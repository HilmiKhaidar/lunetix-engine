#!/usr/bin/env python3

import os
import sys
import subprocess
import glob
from pathlib import Path

def apply_patch(patch_file, target_dir):
    """Apply a single patch file to the target directory."""
    try:
        cmd = ['git', 'apply', '--ignore-whitespace', '--reject', patch_file]
        result = subprocess.run(cmd, cwd=target_dir, capture_output=True, text=True)
        
        if result.returncode == 0:
            print(f"✓ Applied patch: {patch_file}")
            return True
        else:
            print(f"✗ Failed to apply patch: {patch_file}")
            print(f"Error: {result.stderr}")
            return False
    except Exception as e:
        print(f"✗ Exception applying patch {patch_file}: {e}")
        return False

def main():
    script_dir = Path(__file__).parent
    patches_dir = script_dir / '../patches'
    src_dir = script_dir / '../../src'
    
    if not patches_dir.exists():
        print("No patches directory found, skipping patch application")
        return 0
    
    if not src_dir.exists():
        print("Source directory not found")
        return 1
    
    patch_files = sorted(glob.glob(str(patches_dir / '*.patch')))
    
    if not patch_files:
        print("No patch files found")
        return 0
    
    print(f"Applying {len(patch_files)} patches...")
    
    failed_patches = []
    for patch_file in patch_files:
        if not apply_patch(patch_file, src_dir):
            failed_patches.append(patch_file)
    
    if failed_patches:
        print(f"\n{len(failed_patches)} patches failed to apply:")
        for patch in failed_patches:
            print(f"  - {patch}")
        return 1
    
    print(f"\nAll {len(patch_files)} patches applied successfully!")
    return 0

if __name__ == '__main__':
    sys.exit(main())