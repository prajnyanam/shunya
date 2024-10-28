#!/bin/bash

# Directory to start from (current directory by default)
DIR=${1:-.}

# Find all .cc and .h files in the specified directory
FILES=$(find "$DIR" -name "*.cc" -o -name "*.h")

# Check if any files were found
if [ -z "$FILES" ]; then
    echo "No .cc or .h files found in the directory."
    exit 0
fi

# Run clang-tidy on each file
for FILE in $FILES; do
    echo "Running clang-tidy on $FILE"
    clang-tidy "$FILE" -- -std=c++17
done
