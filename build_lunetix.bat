@echo off
setlocal enabledelayedexpansion

echo Building Lunetix Browser...

REM Check if depot_tools is in PATH
where gclient >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: depot_tools not found in PATH
    echo Please install depot_tools and add it to your PATH
    exit /b 1
)

REM Sync Chromium source
echo Syncing Chromium source...
gclient sync --nohooks --no-history

REM Apply Lunetix patches and branding
echo Applying Lunetix customizations...
python lunetix\tools\apply_patches.py
python lunetix\tools\setup_branding.py

REM Run hooks
echo Running gclient hooks...
gclient runhooks

REM Build Lunetix
echo Building Lunetix...
python lunetix\tools\build.py

echo Build completed!
pause