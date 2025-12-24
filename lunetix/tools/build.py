#!/usr/bin/env python3

import os
import sys
import subprocess
import argparse
from pathlib import Path

def run_command(cmd, cwd=None):
    """Run a command and return success status."""
    try:
        print(f"Running: {' '.join(cmd)}")
        result = subprocess.run(cmd, cwd=cwd, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Command failed with exit code {e.returncode}")
        return False

def setup_build_environment():
    """Set up the build environment."""
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    
    if not src_dir.exists():
        print("Source directory not found. Run gclient sync first.")
        return False
    
    # Generate build files
    gn_args = [
        'is_debug=false',
        'is_official_build=true',
        'enable_nacl=false',
        'enable_remoting=false',
        'enable_google_now=false',
        'enable_hotwording=false',
        'enable_print_preview=true',
        'enable_basic_printing=true',
        'enable_spellcheck=true',
        'use_cups=false',
        'proprietary_codecs=true',
        'ffmpeg_branding="Chrome"',
        'lunetix_channel=""',
        'lunetix_version_major="1"',
        'lunetix_version_minor="0"',
        'lunetix_version_build="0"',
        'lunetix_version_patch="0"',
    ]
    
    # Create out directory
    out_dir = src_dir / 'out' / 'Release'
    out_dir.mkdir(parents=True, exist_ok=True)
    
    # Write args.gn
    args_file = out_dir / 'args.gn'
    with open(args_file, 'w') as f:
        f.write('\n'.join(gn_args))
    
    print(f"✓ Created build configuration: {args_file}")
    
    # Run gn gen
    if not run_command(['gn', 'gen', 'out/Release'], cwd=src_dir):
        return False
    
    print("✓ Build environment setup completed")
    return True

def build_lunetix(target='lunetix'):
    """Build Lunetix browser."""
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    
    if not (src_dir / 'out' / 'Release').exists():
        print("Build directory not found. Setting up build environment...")
        if not setup_build_environment():
            return False
    
    # Build the target
    if not run_command(['ninja', '-C', 'out/Release', target], cwd=src_dir):
        return False
    
    print(f"✓ Successfully built {target}")
    return True

def main():
    parser = argparse.ArgumentParser(description='Build Lunetix browser')
    parser.add_argument('--target', default='lunetix', 
                       help='Build target (default: lunetix)')
    parser.add_argument('--setup-only', action='store_true',
                       help='Only setup build environment, do not build')
    
    args = parser.parse_args()
    
    if args.setup_only:
        success = setup_build_environment()
    else:
        success = build_lunetix(args.target)
    
    return 0 if success else 1

if __name__ == '__main__':
    sys.exit(main())