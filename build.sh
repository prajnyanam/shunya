#!/bin/bash

set -e  # Exit immediately on error

# Create build directory if it doesn't exist
mkdir -p build

# Move into build directory
cd build

# Generate build system
cmake -DENABLE_CLANG_FORMAT=ON ..

# Compile the project
cmake --build . -j$(nproc)  # Use all CPU cores