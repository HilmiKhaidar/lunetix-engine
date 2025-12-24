#!/usr/bin/env python3

import os
import sys
import subprocess
import argparse
from pathlib import Path

def run_unit_tests(src_dir, test_filter=None):
    """Run Lunetix unit tests."""
    test_targets = [
        'lunetix_common_unittests',
        'lunetix_browser_tests',
    ]
    
    success = True
    for target in test_targets:
        test_exe = src_dir / 'out' / 'Release' / f'{target}.exe'
        
        if not test_exe.exists():
            print(f"⚠ Test executable not found: {test_exe}")
            continue
        
        cmd = [str(test_exe)]
        if test_filter:
            cmd.extend(['--gtest_filter', test_filter])
        
        print(f"Running {target}...")
        try:
            result = subprocess.run(cmd, cwd=src_dir, check=True)
            print(f"✓ {target} passed")
        except subprocess.CalledProcessError as e:
            print(f"✗ {target} failed with exit code {e.returncode}")
            success = False
    
    return success

def run_integration_tests(src_dir):
    """Run Lunetix integration tests."""
    test_cmd = [
        'python',
        'testing/scripts/run_integration_tests.py',
        '--browser-executable', 'out/Release/lunetix.exe',
        '--test-launcher-jobs', '1',
    ]
    
    print("Running integration tests...")
    try:
        result = subprocess.run(test_cmd, cwd=src_dir, check=True)
        print("✓ Integration tests passed")
        return True
    except subprocess.CalledProcessError as e:
        print(f"✗ Integration tests failed with exit code {e.returncode}")
        return False

def run_performance_tests(src_dir):
    """Run Lunetix performance tests."""
    perf_cmd = [
        'python',
        'tools/perf/run_benchmark',
        '--browser', 'exact',
        '--browser-executable', 'out/Release/lunetix.exe',
        'system_health.memory_desktop',
    ]
    
    print("Running performance tests...")
    try:
        result = subprocess.run(perf_cmd, cwd=src_dir, check=True)
        print("✓ Performance tests completed")
        return True
    except subprocess.CalledProcessError as e:
        print(f"✗ Performance tests failed with exit code {e.returncode}")
        return False

def run_security_tests(src_dir):
    """Run Lunetix security tests."""
    security_targets = [
        'security_tests',
        'sandbox_linux_unittests',
    ]
    
    success = True
    for target in security_targets:
        test_exe = src_dir / 'out' / 'Release' / f'{target}.exe'
        
        if not test_exe.exists():
            print(f"⚠ Security test not found: {test_exe}")
            continue
        
        print(f"Running {target}...")
        try:
            result = subprocess.run([str(test_exe)], cwd=src_dir, check=True)
            print(f"✓ {target} passed")
        except subprocess.CalledProcessError as e:
            print(f"✗ {target} failed with exit code {e.returncode}")
            success = False
    
    return success

def run_smoke_test(src_dir):
    """Run basic smoke test of Lunetix browser."""
    lunetix_exe = src_dir / 'out' / 'Release' / 'lunetix.exe'
    
    if not lunetix_exe.exists():
        print(f"Error: Lunetix executable not found: {lunetix_exe}")
        return False
    
    # Test basic startup and shutdown
    smoke_cmd = [
        str(lunetix_exe),
        '--headless',
        '--disable-gpu',
        '--no-sandbox',
        '--disable-dev-shm-usage',
        '--virtual-time-budget=1000',
        'about:blank',
    ]
    
    print("Running smoke test...")
    try:
        result = subprocess.run(smoke_cmd, cwd=src_dir, timeout=30, 
                              capture_output=True, text=True)
        if result.returncode == 0:
            print("✓ Smoke test passed")
            return True
        else:
            print(f"✗ Smoke test failed: {result.stderr}")
            return False
    except subprocess.TimeoutExpired:
        print("✗ Smoke test timed out")
        return False
    except Exception as e:
        print(f"✗ Smoke test error: {e}")
        return False

def main():
    parser = argparse.ArgumentParser(description='Run Lunetix tests')
    parser.add_argument('--test-type', 
                       choices=['unit', 'integration', 'performance', 'security', 'smoke', 'all'],
                       default='all', help='Type of tests to run')
    parser.add_argument('--filter', help='Test filter pattern')
    parser.add_argument('--src-dir', help='Source directory path')
    
    args = parser.parse_args()
    
    # Determine source directory
    if args.src_dir:
        src_dir = Path(args.src_dir)
    else:
        script_dir = Path(__file__).parent
        src_dir = script_dir / '../../src'
    
    if not src_dir.exists():
        print(f"Error: Source directory not found: {src_dir}")
        return 1
    
    success = True
    
    if args.test_type in ['unit', 'all']:
        success &= run_unit_tests(src_dir, args.filter)
    
    if args.test_type in ['integration', 'all']:
        success &= run_integration_tests(src_dir)
    
    if args.test_type in ['performance', 'all']:
        success &= run_performance_tests(src_dir)
    
    if args.test_type in ['security', 'all']:
        success &= run_security_tests(src_dir)
    
    if args.test_type in ['smoke', 'all']:
        success &= run_smoke_test(src_dir)
    
    if success:
        print("\n✓ All tests passed!")
        return 0
    else:
        print("\n✗ Some tests failed!")
        return 1

if __name__ == '__main__':
    sys.exit(main())