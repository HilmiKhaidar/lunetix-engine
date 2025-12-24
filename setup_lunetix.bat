@echo off
setlocal enabledelayedexpansion

echo Setting up Lunetix development environment...

REM Check if Python is available
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: Python not found. Please install Python 3.7+ and add it to PATH
    exit /b 1
)

REM Check if depot_tools is in PATH
where gclient >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: depot_tools not found in PATH
    echo Please download depot_tools from:
    echo https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up
    echo And add it to your PATH environment variable
    exit /b 1
)

REM Create directory structure
echo Creating directory structure...
if not exist "src" mkdir src

REM Initial gclient sync to get Chromium
echo Performing initial Chromium sync...
echo This may take a while (several GB download)...
gclient sync --nohooks --no-history

REM Apply Lunetix customizations
echo Applying Lunetix patches and branding...
python lunetix\tools\apply_patches.py
python lunetix\tools\setup_branding.py

REM Run gclient hooks
echo Running gclient hooks...
gclient runhooks

echo.
echo ✓ Lunetix development environment setup completed!
echo.
echo Next steps:
echo 1. Run "build_lunetix.bat" to build the browser
echo 2. Or use "python lunetix\tools\build.py" for more options
echo.
pause