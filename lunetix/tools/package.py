#!/usr/bin/env python3

import os
import sys
import shutil
import subprocess
import argparse
from pathlib import Path

def create_installer_package(build_dir, output_dir, version):
    """Create installer package for Lunetix."""
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    
    # Ensure output directory exists
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Copy executable and dependencies
    exe_path = build_dir / 'lunetix.exe'
    if not exe_path.exists():
        print(f"Error: Lunetix executable not found at {exe_path}")
        return False
    
    package_dir = output_dir / f'lunetix-{version}-win64'
    package_dir.mkdir(exist_ok=True)
    
    # Copy main executable
    shutil.copy2(exe_path, package_dir / 'lunetix.exe')
    print(f"✓ Copied executable to {package_dir}")
    
    # Copy required DLLs and resources
    required_files = [
        'chrome_100_percent.pak',
        'chrome_200_percent.pak',
        'resources.pak',
        'icudtl.dat',
        'v8_context_snapshot.bin',
        'snapshot_blob.bin',
    ]
    
    for file_name in required_files:
        src_file = build_dir / file_name
        if src_file.exists():
            shutil.copy2(src_file, package_dir / file_name)
            print(f"✓ Copied {file_name}")
        else:
            print(f"⚠ Missing file: {file_name}")
    
    # Copy locales directory
    locales_src = build_dir / 'locales'
    if locales_src.exists():
        locales_dst = package_dir / 'locales'
        shutil.copytree(locales_src, locales_dst, dirs_exist_ok=True)
        print("✓ Copied locales directory")
    
    # Create version info file
    version_file = package_dir / 'VERSION'
    with open(version_file, 'w') as f:
        f.write(f"Lunetix {version}\n")
        f.write(f"Build date: {subprocess.check_output(['date'], text=True).strip()}\n")
    
    print(f"✓ Created package: {package_dir}")
    return True

def create_zip_archive(package_dir, output_dir):
    """Create ZIP archive of the package."""
    package_path = Path(package_dir)
    output_path = Path(output_dir)
    
    zip_name = f"{package_path.name}.zip"
    zip_path = output_path / zip_name
    
    # Create ZIP archive
    shutil.make_archive(str(zip_path.with_suffix('')), 'zip', 
                       package_path.parent, package_path.name)
    
    print(f"✓ Created ZIP archive: {zip_path}")
    return zip_path

def create_installer_script(package_dir, version):
    """Create installer script for Lunetix."""
    installer_script = f"""@echo off
echo Installing Lunetix {version}...

set INSTALL_DIR=%PROGRAMFILES%\\Lunetix
set DESKTOP_SHORTCUT=%USERPROFILE%\\Desktop\\Lunetix.lnk
set STARTMENU_SHORTCUT=%APPDATA%\\Microsoft\\Windows\\Start Menu\\Programs\\Lunetix.lnk

echo Creating installation directory...
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"

echo Copying files...
xcopy /E /I /Y * "%INSTALL_DIR%"

echo Creating shortcuts...
powershell "$WshShell = New-Object -comObject WScript.Shell; $Shortcut = $WshShell.CreateShortcut('%DESKTOP_SHORTCUT%'); $Shortcut.TargetPath = '%INSTALL_DIR%\\lunetix.exe'; $Shortcut.Save()"
powershell "$WshShell = New-Object -comObject WScript.Shell; $Shortcut = $WshShell.CreateShortcut('%STARTMENU_SHORTCUT%'); $Shortcut.TargetPath = '%INSTALL_DIR%\\lunetix.exe'; $Shortcut.Save()"

echo Lunetix {version} installed successfully!
echo You can now run Lunetix from the Start Menu or Desktop shortcut.
pause
"""
    
    installer_path = Path(package_dir) / 'install.bat'
    with open(installer_path, 'w') as f:
        f.write(installer_script)
    
    print(f"✓ Created installer script: {installer_path}")
    return installer_path

def main():
    parser = argparse.ArgumentParser(description='Package Lunetix browser')
    parser.add_argument('--build-dir', required=True,
                       help='Build directory containing lunetix.exe')
    parser.add_argument('--output-dir', default='dist',
                       help='Output directory for packages')
    parser.add_argument('--version', default='1.0.0',
                       help='Version string for package')
    parser.add_argument('--create-zip', action='store_true',
                       help='Create ZIP archive')
    parser.add_argument('--create-installer', action='store_true',
                       help='Create installer script')
    
    args = parser.parse_args()
    
    build_dir = Path(args.build_dir)
    if not build_dir.exists():
        print(f"Error: Build directory not found: {build_dir}")
        return 1
    
    # Create package
    if not create_installer_package(build_dir, args.output_dir, args.version):
        return 1
    
    package_dir = Path(args.output_dir) / f'lunetix-{args.version}-win64'
    
    # Create installer script
    if args.create_installer:
        create_installer_script(package_dir, args.version)
    
    # Create ZIP archive
    if args.create_zip:
        create_zip_archive(package_dir, args.output_dir)
    
    print(f"\n✓ Packaging completed successfully!")
    print(f"Package location: {package_dir}")
    
    return 0

if __name__ == '__main__':
    sys.exit(main())