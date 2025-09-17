@echo off
REM Simple build script for Smart Traffic Management System
REM This script compiles the project without requiring CMake

echo Building Smart Traffic Management System...
echo.

REM Create build directory if it doesn't exist
if not exist "build" mkdir build
cd build

REM Check for g++ compiler
where g++ >nul 2>nul
if %errorlevel% == 0 (
    echo Using g++ compiler...
    g++ -std=c++17 -pthread -I../include -o smart_traffic_system.exe ../main.cpp ../src/*.cpp
    if %errorlevel% == 0 (
        echo.
        echo Build successful! Executable created: smart_traffic_system.exe
        echo.
        echo To run the program:
        echo   .\smart_traffic_system.exe
        echo.
    ) else (
        echo Build failed with g++
    )
    goto :end
)

REM Check for clang++ compiler
where clang++ >nul 2>nul
if %errorlevel% == 0 (
    echo Using clang++ compiler...
    clang++ -std=c++17 -pthread -I../include -o smart_traffic_system.exe ../main.cpp ../src/*.cpp
    if %errorlevel% == 0 (
        echo.
        echo Build successful! Executable created: smart_traffic_system.exe
        echo.
        echo To run the program:
        echo   .\smart_traffic_system.exe
        echo.
    ) else (
        echo Build failed with clang++
    )
    goto :end
)

REM Check for MSVC compiler
where cl >nul 2>nul
if %errorlevel% == 0 (
    echo Using MSVC compiler...
    cl /std:c++17 /EHsc /I..\include ..\main.cpp ..\src\*.cpp /Fe:smart_traffic_system.exe
    if %errorlevel% == 0 (
        echo.
        echo Build successful! Executable created: smart_traffic_system.exe
        echo.
        echo To run the program:
        echo   .\smart_traffic_system.exe
        echo.
    ) else (
        echo Build failed with MSVC
    )
    goto :end
)

echo Error: No suitable C++ compiler found!
echo Please install one of the following:
echo   - MinGW-w64 (g++)
echo   - LLVM/Clang (clang++)
echo   - Visual Studio Build Tools (cl)
echo.

:end
cd ..
pause