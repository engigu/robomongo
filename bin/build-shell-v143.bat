@echo off
setlocal enableextensions enabledelayedexpansion

rem ===========================================================================
rem Robo Shell Build Script for VS 2022 (v143)
rem ===========================================================================

set "PROJECT_ROOT=%~dp0.."
set "SHELL_DIR=%PROJECT_ROOT%\robo-shell"
set "REPO_URL=https://github.com/paralect/robomongo-shell.git"
set "REPO_BRANCH=roboshell-v4.2"

if not exist "%SHELL_DIR%" (
    echo [0/4] Cloning Robo Shell from remote (!REPO_BRANCH!)...
    cd /d "%PROJECT_ROOT%"
    git clone --depth 1 -b !REPO_BRANCH! !REPO_URL! robo-shell
    if %ERRORLEVEL% neq 0 (
        echo Error: Failed to clone repository.
        exit /b 1
    )
) else (
    echo [0/4] Using existing Robo Shell directory: %SHELL_DIR%
)

echo [1/4] Searching for Visual Studio 2022...
set "VS_WHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VCVARSALL="

if exist "%VS_WHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VS_WHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VS_PATH=%%i"
    )
    if exist "!VS_PATH!\VC\Auxiliary\Build\vcvarsall.bat" (
        set "VCVARSALL=!VS_PATH!\VC\Auxiliary\Build\vcvarsall.bat"
    )
)

if "!VCVARSALL!"=="" (
    echo Error: Visual Studio 2022 C++ Build Tools not found!
    echo Please ensure "Desktop development with C++" workload is installed.
    exit /b 1
)

echo Found: !VCVARSALL!

echo [2/4] Setting up MSVC v143 Environment...
call "!VCVARSALL!" x64 -vcvars_ver=14.3

echo [3/4] Ensuring SCons and dependencies are installed...
python -m pip install scons==4.5.2 pyyaml

echo [4/4] Applying patches and building...
cd /d "%PROJECT_ROOT%"
python fix\apply_patches.py

cd /d "%SHELL_DIR%"
echo Starting SCons build. This will take a while...
python -m SCons mongo.exe MONGO_VERSION=4.2.0 --release -j%NUMBER_OF_PROCESSORS% --link-model=object

if %ERRORLEVEL% equ 0 (
    echo.
    echo ===========================================================================
    echo SUCCESS: Robo Shell built successfully with VS 2022 (v143)
    echo ===========================================================================
) else (
    echo.
    echo ===========================================================================
    echo ERROR: Robo Shell build failed!
    echo ===========================================================================
    exit /b 1
)

pause
