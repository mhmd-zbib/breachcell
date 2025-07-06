#!/bin/zsh
# Build and run the project

set -e

BUILD_DIR="build"
EXECUTABLE="CppProject"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Run CMake and Make
cmake ..
make

# Run the executable (adjust name if needed)
if [ -f "$EXECUTABLE" ]; then
    echo "Running $EXECUTABLE..."
    ./$EXECUTABLE
else
    echo "Executable $EXECUTABLE not found. Please check the name."
    exit 1
fi
