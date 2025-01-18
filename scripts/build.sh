#!/bin/bash

if [ -d "build" ]; then
    echo
    echo "Found build directory. Deleting..."
    rm -r "build"
    echo "build directory deleted."
fi

if [ -d "dist" ]; then
    echo
    echo "Found dist directory. Deleting..."
    rm -r "dist"
    echo "dist directory deleted."
fi

echo ""

mkdir build
echo "New build directory created."

cd build

echo ""

echo "X------Generating build files------X"
cmake ..
echo "X------Build files generated. Ready to compile------X"

echo ""

echo "X------Compiling the project------X"
cmake --build .
echo "X------Project is compiled. Ready to install-----X"

echo ""

echo "X------Installing the project------X"
cmake --install . --prefix ../dist
echo "X------Project is installed -----X"

echo ""

echo "Build task completed."

echo ""
