@echo off
cd /d "%~dp0"

echo ========================================
echo    Starstruck Game Launcher
echo ========================================
echo.

if not exist "build\Starstruck.exe" (
    echo Building Starstruck...
    
    if exist "build" rmdir /s /q build
    mkdir build
    cd build
    
    echo Configuring CMake...
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    if errorlevel 1 (
        echo CMake failed!
        pause
        exit /b 1
    )
    
    echo Compiling...
    mingw32-make
    if errorlevel 1 (
        echo Compilation failed!
        pause
        exit /b 1
    )
    
    echo Copying DLLs...
    if exist "..\libs\SFML\bin\*.dll" copy "..\libs\SFML\bin\*.dll" . > nul
    
    echo Copying assets...
    if exist "..\assets" xcopy /E /I /Y "..\assets" "assets" > nul
    
    cd ..
    echo.
)

cd build
start "" "Starstruck.exe"
cd ..
exit