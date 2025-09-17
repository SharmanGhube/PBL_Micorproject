#!/bin/bash
# Simple build script for Smart Traffic Management System (Linux/macOS)
# This script compiles the project without requiring CMake

echo "Building Smart Traffic Management System..."
echo

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Check for g++ compiler
if command -v g++ &> /dev/null; then
    echo "Using g++ compiler..."
    g++ -std=c++17 -pthread -I../include -o smart_traffic_system ../main.cpp ../src/*.cpp
    if [ $? -eq 0 ]; then
        echo
        echo "Build successful! Executable created: smart_traffic_system"
        echo
        echo "To run the program:"
        echo "  ./smart_traffic_system"
        echo
    else
        echo "Build failed with g++"
    fi
    exit 0
fi

# Check for clang++ compiler
if command -v clang++ &> /dev/null; then
    echo "Using clang++ compiler..."
    clang++ -std=c++17 -pthread -I../include -o smart_traffic_system ../main.cpp ../src/*.cpp
    if [ $? -eq 0 ]; then
        echo
        echo "Build successful! Executable created: smart_traffic_system"
        echo
        echo "To run the program:"
        echo "  ./smart_traffic_system"
        echo
    else
        echo "Build failed with clang++"
    fi
    exit 0
fi

echo "Error: No suitable C++ compiler found!"
echo "Please install one of the following:"
echo "  - GCC (g++): sudo apt-get install build-essential"
echo "  - Clang (clang++): sudo apt-get install clang"
echo

cd ..