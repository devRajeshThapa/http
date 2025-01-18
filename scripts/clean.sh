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
    echo
fi
