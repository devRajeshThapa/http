#!/bin/bash

# Remove build directory if it exists
if [ -d "build" ]; then
    rm -rf build
    echo "Removed existing build directory."
fi

# Remove dist directory if it exists
if [ -d "dist" ]; then
    rm -rf dist
    echo "Removed existing dist directory."
fi

echo ""

# Create build directory
mkdir build
echo "x------Created build directory------x"
cd build

echo ""

# Generate build files
echo "x------Generating build files------x"
cmake -G "Unix Makefiles" ..
echo "x------Generated build files------x"

echo ""

# Compile the project
echo "x------Compiling the project------x"
cmake --build .
echo "x------Compiled the project------x"

echo ""

# Install the project
echo "x------Installing the project------x"
cmake --install . --prefix ../dist
echo "x------Installed the project------x"