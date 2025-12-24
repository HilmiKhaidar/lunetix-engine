#!/usr/bin/env python3

import os
import sys
import shutil
import json
from pathlib import Path

def copy_branding_files():
    """Copy Lunetix branding files to appropriate locations."""
    script_dir = Path(__file__).parent
    branding_dir = script_dir / '../branding'
    src_dir = script_dir / '../../src'
    
    if not branding_dir.exists():
        print("No branding directory found")
        return False
    
    branding_mappings = [
        ('icons/lunetix_16.png', 'chrome/app/theme/default_100_percent/lunetix_16.png'),
        ('icons/lunetix_32.png', 'chrome/app/theme/default_100_percent/lunetix_32.png'),
        ('icons/lunetix_48.png', 'chrome/app/theme/default_100_percent/lunetix_48.png'),
        ('icons/lunetix_64.png', 'chrome/app/theme/default_100_percent/lunetix_64.png'),
        ('icons/lunetix_128.png', 'chrome/app/theme/default_100_percent/lunetix_128.png'),
        ('icons/lunetix_256.png', 'chrome/app/theme/default_100_percent/lunetix_256.png'),
        ('icons/lunetix.ico', 'chrome/app/theme/lunetix.ico'),
        ('strings/lunetix_strings.grd', 'chrome/app/lunetix_strings.grd'),
    ]
    
    for src_file, dest_file in branding_mappings:
        src_path = branding_dir / src_file
        dest_path = src_dir / dest_file
        
        if src_path.exists():
            dest_path.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src_path, dest_path)
            print(f"✓ Copied {src_file} to {dest_file}")
        else:
            print(f"⚠ Branding file not found: {src_file}")
    
    return True

def update_version_info():
    """Update version information files."""
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    
    version_file = src_dir / 'chrome/VERSION'
    if version_file.exists():
        with open(version_file, 'r') as f:
            content = f.read()
        
        # Update version info for Lunetix
        content = content.replace('MAJOR=', 'MAJOR=1')
        content = content.replace('MINOR=', 'MINOR=0')
        content = content.replace('BUILD=', 'BUILD=0')
        content = content.replace('PATCH=', 'PATCH=0')
        
        with open(version_file, 'w') as f:
            f.write(content)
        
        print("✓ Updated version information")
    
    return True

def main():
    print("Setting up Lunetix branding...")
    
    success = True
    success &= copy_branding_files()
    success &= update_version_info()
    
    if success:
        print("✓ Branding setup completed successfully!")
        return 0
    else:
        print("✗ Branding setup failed")
        return 1

if __name__ == '__main__':
    sys.exit(main())