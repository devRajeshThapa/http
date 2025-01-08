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