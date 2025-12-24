#!/usr/bin/env python3

import os
import sys
import subprocess
import json
import time
from pathlib import Path

def setup_ci_environment():
    """Setup CI environment variables and dependencies."""
    env_vars = {
        'DEPOT_TOOLS_WIN_TOOLCHAIN': '0',
        'GYP_MSVS_VERSION': '2022',
        'LUNETIX_BUILD': '1',
        'OFFICIAL_BUILD': '1',
    }
    
    for key, value in env_vars.items():
        os.environ[key] = value
        print(f"Set {key}={value}")
    
    return True

def sync_and_patch():
    """Sync Chromium source and apply Lunetix patches."""
    script_dir = Path(__file__).parent
    
    # Sync Chromium
    sync_cmd = ['python', str(script_dir / 'sync_chromium.py'), '--revision', 'main']
    if not run_command(sync_cmd):
        return False
    
    # Apply patches
    patch_cmd = ['python', str(script_dir / 'apply_patches.py')]
    if not run_command(patch_cmd):
        return False
    
    # Setup branding
    branding_cmd = ['python', str(script_dir / 'setup_branding.py')]
    if not run_command(branding_cmd):
        return False
    
    return True

def build_lunetix():
    """Build Lunetix browser."""
    script_dir = Path(__file__).parent
    
    build_cmd = ['python', str(script_dir / 'build.py'), '--target', 'lunetix']
    return run_command(build_cmd)

def run_tests():
    """Run test suite."""
    script_dir = Path(__file__).parent
    
    test_cmd = ['python', str(script_dir / 'test_runner.py'), '--test-type', 'smoke']
    return run_command(test_cmd)

def package_build():
    """Package the build for distribution."""
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    build_dir = src_dir / 'out' / 'Release'
    
    if not build_dir.exists():
        print("Error: Build directory not found")
        return False
    
    # Get version info
    version = get_lunetix_version()
    
    package_cmd = [
        'python', str(script_dir / 'package.py'),
        '--build-dir', str(build_dir),
        '--output-dir', 'dist',
        '--version', version,
        '--create-zip',
        '--create-installer'
    ]
    
    return run_command(package_cmd)

def get_lunetix_version():
    """Get Lunetix version from build configuration."""
    script_dir = Path(__file__).parent
    build_gn = script_dir / '../BUILD.gn'
    
    if not build_gn.exists():
        return '1.0.0'
    
    with open(build_gn, 'r') as f:
        content = f.read()
    
    import re
    major = re.search(r'lunetix_version_major = "(\d+)"', content)
    minor = re.search(r'lunetix_version_minor = "(\d+)"', content)
    build = re.search(r'lunetix_version_build = "(\d+)"', content)
    patch = re.search(r'lunetix_version_patch = "(\d+)"', content)
    
    if all([major, minor, build, patch]):
        return f"{major.group(1)}.{minor.group(1)}.{build.group(1)}.{patch.group(1)}"
    
    return '1.0.0'

def run_command(cmd, cwd=None):
    """Run a command and return success status."""
    try:
        print(f"Running: {' '.join(cmd)}")
        result = subprocess.run(cmd, cwd=cwd, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Command failed with exit code {e.returncode}")
        return False

def generate_build_report():
    """Generate build report with metrics."""
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    build_dir = src_dir / 'out' / 'Release'
    
    report = {
        'timestamp': time.time(),
        'version': get_lunetix_version(),
        'build_success': build_dir.exists(),
        'executable_size': 0,
        'total_build_size': 0,
    }
    
    if build_dir.exists():
        lunetix_exe = build_dir / 'lunetix.exe'
        if lunetix_exe.exists():
            report['executable_size'] = lunetix_exe.stat().st_size
        
        # Calculate total build size
        total_size = 0
        for file_path in build_dir.rglob('*'):
            if file_path.is_file():
                total_size += file_path.stat().st_size
        report['total_build_size'] = total_size
    
    # Write report
    report_file = Path('build_report.json')
    with open(report_file, 'w') as f:
        json.dump(report, f, indent=2)
    
    print(f"✓ Build report generated: {report_file}")
    return True

def main():
    print("Starting Lunetix CI build...")
    start_time = time.time()
    
    steps = [
        ("Setup CI environment", setup_ci_environment),
        ("Sync and patch", sync_and_patch),
        ("Build Lunetix", build_lunetix),
        ("Run tests", run_tests),
        ("Package build", package_build),
        ("Generate report", generate_build_report),
    ]
    
    for step_name, step_func in steps:
        print(f"\n=== {step_name} ===")
        if not step_func():
            print(f"✗ {step_name} failed")
            return 1
        print(f"✓ {step_name} completed")
    
    elapsed_time = time.time() - start_time
    print(f"\n✓ CI build completed successfully in {elapsed_time:.1f} seconds")
    
    return 0

if __name__ == '__main__':
    sys.exit(main())