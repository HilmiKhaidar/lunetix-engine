@echo off
title Lunetix Browser - React Build
color 0B
cls

echo.
echo  ██╗     ██╗   ██╗███╗   ██╗███████╗████████╗██╗██╗  ██╗
echo  ██║     ██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║╚██╗██╔╝
echo  ██║     ██║   ██║██╔██╗ ██║█████╗     ██║   ██║ ╚███╔╝ 
echo  ██║     ██║   ██║██║╚██╗██║██╔══╝     ██║   ██║ ██╔██╗ 
echo  ███████╗╚██████╔╝██║ ╚████║███████╗   ██║   ██║██╔╝ ██╗
echo  ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝╚═╝  ╚═╝
echo.
echo  ========================================================
echo  📦 LUNETIX BROWSER - REACT BUILD SYSTEM
echo  Building React + Tailwind UI Components
echo  ========================================================
echo.

REM Check if Node.js is installed
node --version >nul 2>&1
if errorlevel 1 (
    echo ❌ Node.js not found!
    echo.
    echo Please install Node.js from: https://nodejs.org/
    echo Recommended version: Node.js 18+ with npm
    echo.
    pause
    exit /b 1
)

echo ✅ Node.js found: 
node --version
echo.

REM Navigate to React project directory
if not exist "lunetix\ui-react" (
    echo ❌ React project directory not found!
    echo Expected: lunetix\ui-react\
    echo.
    pause
    exit /b 1
)

cd lunetix\ui-react

REM Check if package.json exists
if not exist "package.json" (
    echo ❌ package.json not found!
    echo.
    pause
    exit /b 1
)

echo 🔍 Checking React project structure...
echo.

REM Install dependencies if node_modules doesn't exist
if not exist "node_modules" (
    echo 📦 Installing React dependencies...
    echo.
    echo Installing:
    echo • React 18 + React DOM
    echo • Tailwind CSS + PostCSS
    echo • Vite (Build Tool)
    echo • Framer Motion (Animations)
    echo • Lucide React (Icons)
    echo.
    call npm install
    if errorlevel 1 (
        echo ❌ Failed to install dependencies!
        pause
        exit /b 1
    )
    echo ✅ Dependencies installed successfully!
    echo.
) else (
    echo ✅ Dependencies already installed
    echo.
)

echo 🏗️ Building React UI for production...
echo.
echo Build targets:
echo • index.html (Main entry)
echo • mobile.html (Mobile interface)
echo • desktop.html (Desktop interface) 
echo • ecosystem.html (Demo showcase)
echo.

call npm run build
if errorlevel 1 (
    echo ❌ Build failed!
    echo.
    echo Common issues:
    echo • Check for syntax errors in React components
    echo • Verify all imports are correct
    echo • Ensure Tailwind config is valid
    echo.
    pause
    exit /b 1
)

echo.
echo ✅ React UI built successfully!
echo.

REM Check if build output exists
cd ..\..
if exist "lunetix\browser\ui\dist" (
    echo 📁 Build output location: lunetix\browser\ui\dist\
    echo.
    echo 📄 Generated files:
    dir /b lunetix\browser\ui\dist\*.html 2>nul
    echo.
    echo 📊 Build statistics:
    for %%f in (lunetix\browser\ui\dist\*.html) do (
        echo • %%~nxf - %%~zf bytes
    )
    echo.
) else (
    echo ❌ Build output not found!
    echo Expected: lunetix\browser\ui\dist\
    pause
    exit /b 1
)

echo 🎯 Next steps:
echo.
echo 1. Run: start_lunetix_react.bat
echo 2. Choose your preferred interface:
echo    • Mobile (React + iOS 17 design)
echo    • Desktop (React + macOS Sonoma design)  
echo    • Ecosystem (Complete demo)
echo.
echo 🌟 React + Tailwind features ready:
echo • Component-based architecture
echo • Apple-inspired design system
echo • Responsive layouts
echo • Smooth animations
echo • Modern JavaScript (ES2023+)
echo.

pause