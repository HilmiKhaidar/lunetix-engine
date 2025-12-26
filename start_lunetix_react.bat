@echo off
title Lunetix Browser - React + Tailwind
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
echo  🚀 LUNETIX BROWSER - REACT + TAILWIND
echo  Modern UI with React Components and Tailwind CSS
echo  ========================================================
echo.

REM Check if browser exists
if not exist "chromium_binary\chrome-win\chrome.exe" (
    echo ❌ Browser not found! 
    echo.
    echo Please run: get_chromium_binary.bat first
    echo.
    pause
    exit /b 1
)

REM Check if React build exists
if not exist "lunetix\browser\ui\dist" (
    echo ❌ React UI not built yet!
    echo.
    echo Please build React UI first:
    echo   cd lunetix/ui-react
    echo   npm install
    echo   npm run build
    echo.
    pause
    exit /b 1
)

REM Create lunetix.exe if not exists
if not exist "chromium_binary\chrome-win\lunetix.exe" (
    echo 🔧 Creating Lunetix executable...
    copy chromium_binary\chrome-win\chrome.exe chromium_binary\chrome-win\lunetix.exe >nul
    echo ✅ Lunetix executable created
    echo.
)

echo 🎯 Choose Lunetix React Mode:
echo.
echo  ┌─────────────────────────────────────────────────────┐
echo  │                 ⚛️ REACT INTERFACES                 │
echo  ├─────────────────────────────────────────────────────┤
echo  │ [1] 📱 Mobile Interface (React + Tailwind)         │
echo  │ [2] 💻 Desktop Interface (React + Tailwind)        │
echo  │ [3] 🌟 Complete Ecosystem Demo                     │
echo  ├─────────────────────────────────────────────────────┤
echo  │                 🌐 STANDARD MODES                   │
echo  ├─────────────────────────────────────────────────────┤
echo  │ [4] 🌐 Standard Browser                            │
echo  │ [5] 🛡️ Privacy Mode                               │
echo  ├─────────────────────────────────────────────────────┤
echo  │                 🔧 DEVELOPMENT                      │
echo  ├─────────────────────────────────────────────────────┤
echo  │ [D] 🔨 Start React Dev Server                      │
echo  │ [B] 📦 Build React UI                             │
echo  │ [H] ❓ Help                                        │
echo  └─────────────────────────────────────────────────────┘
echo.
set /p choice="Enter your choice: "

echo.

if /i "%choice%"=="1" goto mobile
if /i "%choice%"=="2" goto desktop
if /i "%choice%"=="3" goto ecosystem
if /i "%choice%"=="4" goto standard
if /i "%choice%"=="5" goto privacy
if /i "%choice%"=="D" goto dev
if /i "%choice%"=="B" goto build
if /i "%choice%"=="H" goto help
goto ecosystem

:mobile
echo 📱 Starting React Mobile Interface...
echo.
echo Features:
echo • React components with Tailwind CSS
echo • iOS 17 inspired design
echo • Responsive mobile-first layout
echo • Modern JavaScript (ES2023+)
echo.
cd chromium_binary\chrome-win
start "" "lunetix.exe" --app="file:///%CD%/../../lunetix/browser/ui/dist/mobile.html" --window-size=400,900 --user-data-dir="%APPDATA%\LunetixReactMobile" --disable-web-security --allow-file-access-from-files
cd ..\..
goto end

:desktop
echo 💻 Starting React Desktop Interface...
echo.
echo Features:
echo • React components with Tailwind CSS
echo • macOS Sonoma inspired design
echo • Desktop-optimized layout
echo • Component-based architecture
echo.
cd chromium_binary\chrome-win
start "" "lunetix.exe" --app="file:///%CD%/../../lunetix/browser/ui/dist/desktop.html" --window-size=1200,800 --user-data-dir="%APPDATA%\LunetixReactDesktop" --disable-web-security --allow-file-access-from-files
cd ..\..
goto end

:ecosystem
echo 🌟 Starting React Ecosystem Demo...
echo.
echo Features:
echo • Complete React + Tailwind showcase
echo • Mobile & Desktop components
echo • Modern development stack
echo • Interactive demonstrations
echo.
cd chromium_binary\chrome-win
start "" "lunetix.exe" --app="file:///%CD%/../../lunetix/browser/ui/dist/ecosystem.html" --window-size=1400,1000 --user-data-dir="%APPDATA%\LunetixReactEcosystem" --disable-web-security --allow-file-access-from-files
cd ..\..
goto end

:standard
echo 🌐 Starting Standard Browser...
cd chromium_binary\chrome-win
start "" "lunetix.exe" --app-name="Lunetix Browser" --user-data-dir="%APPDATA%\Lunetix"
cd ..\..
goto end

:privacy
echo 🛡️ Starting Privacy Mode...
cd chromium_binary\chrome-win
start "" "lunetix.exe" --incognito --app-name="Lunetix Privacy" --user-data-dir="%TEMP%\LunetixPrivacy"
cd ..\..
goto end

:dev
echo 🔨 Starting React Development Server...
echo.
echo This will start Vite dev server on http://localhost:3000
echo You can then access the interfaces in development mode.
echo.
cd lunetix\ui-react
start cmd /k "npm run dev"
cd ..\..
echo ✅ Dev server started in new window
goto end

:build
echo 📦 Building React UI...
echo.
cd lunetix\ui-react
call npm install
call npm run build
cd ..\..
echo ✅ React UI built successfully
goto end

:help
echo ❓ Lunetix React Help
echo.
echo 📖 REACT + TAILWIND STACK:
echo   • React 18 with modern hooks
echo   • Tailwind CSS for styling
echo   • Vite for fast development
echo   • Framer Motion for animations
echo.
echo 🔧 DEVELOPMENT COMMANDS:
echo   • npm run dev - Start dev server
echo   • npm run build - Build for production
echo   • npm run preview - Preview build
echo.
echo 📁 PROJECT STRUCTURE:
echo   • lunetix/ui-react/src/ - React components
echo   • lunetix/browser/ui/dist/ - Built files
echo.
pause
goto menu

:menu
cls
goto start

:end
echo.
echo ✅ Lunetix Browser launched successfully!
echo.
echo 💡 React + Tailwind Features:
echo   • Modern component architecture
echo   • Utility-first CSS with Tailwind
echo   • Fast development with Vite
echo   • Responsive design system
echo.
echo 🌟 Enjoy your modern Lunetix Browser experience!
echo.
pause