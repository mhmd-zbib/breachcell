#!/bin/bash
set -e

BUILD_DIR="build"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Run CMake and build
cmake -S . -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"

# Find the executable (assumes project name is BreachCell2DGame)
EXECUTABLE="$BUILD_DIR/BreachCell2DGame"
if [ -f "$EXECUTABLE" ]; then
    echo "Running $EXECUTABLE..."
    "$EXECUTABLE"
else
    echo "Executable not found: $EXECUTABLE"
    exit 1
fi
