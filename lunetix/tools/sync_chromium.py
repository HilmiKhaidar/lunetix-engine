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
        result = subprocess.run(cmd, cwd=cwd, check=True, capture_output=True, text=True)
        if result.stdout:
            print(result.stdout)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Command failed with exit code {e.returncode}")
        if e.stderr:
            print(f"Error: {e.stderr}")
        return False

def sync_chromium(no_history=True, reset_to_revision=None):
    """Sync Chromium source code."""
    script_dir = Path(__file__).parent
    root_dir = script_dir / '../..'
    
    # Check if .gclient exists
    gclient_file = root_dir / '.gclient'
    if not gclient_file.exists():
        print("Error: .gclient file not found. Please run from the correct directory.")
        return False
    
    # Prepare gclient sync command
    sync_cmd = ['gclient', 'sync']
    
    if no_history:
        sync_cmd.append('--no-history')
    
    sync_cmd.extend(['--nohooks', '--delete_unversioned_trees'])
    
    if reset_to_revision:
        sync_cmd.extend(['--revision', f'src@{reset_to_revision}'])
    
    # Run gclient sync
    if not run_command(sync_cmd, cwd=root_dir):
        return False
    
    print("✓ Chromium source sync completed")
    return True

def main():
    parser = argparse.ArgumentParser(description='Sync Chromium source code')
    parser.add_argument('--with-history', action='store_true',
                       help='Include git history (slower)')
    parser.add_argument('--revision', type=str,
                       help='Sync to specific Chromium revision')
    
    args = parser.parse_args()
    
    success = sync_chromium(
        no_history=not args.with_history,
        reset_to_revision=args.revision
    )
    
    return 0 if success else 1

if __name__ == '__main__':
    sys.exit(main())