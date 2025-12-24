#!/usr/bin/env python3

import os
import sys
import re
import argparse
from pathlib import Path

def update_version_files(major, minor, build, patch):
    """Update version information in various files."""
    script_dir = Path(__file__).parent
    
    # Update BUILD.gn
    build_gn = script_dir / '../BUILD.gn'
    if build_gn.exists():
        with open(build_gn, 'r') as f:
            content = f.read()
        
        content = re.sub(r'lunetix_version_major = "\d+"', f'lunetix_version_major = "{major}"', content)
        content = re.sub(r'lunetix_version_minor = "\d+"', f'lunetix_version_minor = "{minor}"', content)
        content = re.sub(r'lunetix_version_build = "\d+"', f'lunetix_version_build = "{build}"', content)
        content = re.sub(r'lunetix_version_patch = "\d+"', f'lunetix_version_patch = "{patch}"', content)
        
        with open(build_gn, 'w') as f:
            f.write(content)
        Codebase ini sekarang mencakup semua komponen fundamental yang diperlukan untuk browser production-ready dengan maintainable patch system, comprehensive testing, dan automated build pipeline.
        print(f"✓ Updated {build_gn}")
    
    # Update constants
    constants_cc = script_dir / '../common/lunetix_constants.cc'
    if constants_cc.exists():
        with open(constants_cc, 'r') as f:
            content = f.read()
        
        version_string = f"{major}.{minor}.{build}.{patch}"
        content = re.sub(r'const char kLunetixVersionString\[\] = "[^"]*";', 
                        f'const char kLunetixVersionString[] = "{version_string}";', content)
        
        with open(constants_cc, 'w') as f:
            f.write(content)
        
        print(f"✓ Updated {constants_cc}")
    
    # Update resource file
    exe_rc = script_dir / '../app/lunetix_exe.rc'
    if exe_rc.exists():
        with open(exe_rc, 'r') as f:
            content = f.read()
        
        content = re.sub(r'FILEVERSION \d+,\d+,\d+,\d+', f'FILEVERSION {major},{minor},{build},{patch}', content)
        content = re.sub(r'PRODUCTVERSION \d+,\d+,\d+,\d+', f'PRODUCTVERSION {major},{minor},{build},{patch}', content)
        content = re.sub(r'"FileVersion", "[^"]*"', f'"FileVersion", "{major}.{minor}.{build}.{patch}"', content)
        content = re.sub(r'"ProductVersion", "[^"]*"', f'"ProductVersion", "{major}.{minor}.{build}.{patch}"', content)
        
        with open(exe_rc, 'w') as f:
            f.write(content)
        
        print(f"✓ Updated {exe_rc}")
    
    return True

def get_current_version():
    """Get current version from BUILD.gn file."""
    script_dir = Path(__file__).parent
    build_gn = script_dir / '../BUILD.gn'
    
    if not build_gn.exists():
        return None
    
    with open(build_gn, 'r') as f:
        content = f.read()
    
    major_match = re.search(r'lunetix_version_major = "(\d+)"', content)
    minor_match = re.search(r'lunetix_version_minor = "(\d+)"', content)
    build_match = re.search(r'lunetix_version_build = "(\d+)"', content)
    patch_match = re.search(r'lunetix_version_patch = "(\d+)"', content)
    
    if all([major_match, minor_match, build_match, patch_match]):
        return (
            int(major_match.group(1)),
            int(minor_match.group(1)),
            int(build_match.group(1)),
            int(patch_match.group(1))
        )
    
    return None

def main():
    parser = argparse.ArgumentParser(description='Update Lunetix version')
    parser.add_argument('--major', type=int, help='Major version number')
    parser.add_argument('--minor', type=int, help='Minor version number')
    parser.add_argument('--build', type=int, help='Build version number')
    parser.add_argument('--patch', type=int, help='Patch version number')
    parser.add_argument('--increment', choices=['major', 'minor', 'build', 'patch'],
                       help='Increment specific version component')
    parser.add_argument('--show', action='store_true', help='Show current version')
    
    args = parser.parse_args()
    
    current_version = get_current_version()
    
    if args.show:
        if current_version:
            print(f"Current version: {'.'.join(map(str, current_version))}")
        else:
            print("Could not determine current version")
        return 0
    
    if args.increment:
        if not current_version:
            print("Could not determine current version for increment")
            return 1
        
        major, minor, build, patch = current_version
        
        if args.increment == 'major':
            major += 1
            minor = 0
            build = 0
            patch = 0
        elif args.increment == 'minor':
            minor += 1
            build = 0
            patch = 0
        elif args.increment == 'build':
            build += 1
            patch = 0
        elif args.increment == 'patch':
            patch += 1
    else:
        major = args.major or (current_version[0] if current_version else 1)
        minor = args.minor or (current_version[1] if current_version else 0)
        build = args.build or (current_version[2] if current_version else 0)
        patch = args.patch or (current_version[3] if current_version else 0)
    
    print(f"Updating version to: {major}.{minor}.{build}.{patch}")
    
    if update_version_files(major, minor, build, patch):
        print("✓ Version update completed")
        return 0
    else:
        print("✗ Version update failed")
        return 1

if __name__ == '__main__':
    sys.exit(main())