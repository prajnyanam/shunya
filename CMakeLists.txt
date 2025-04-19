cmake_minimum_required(VERSION 3.16)

# Project name and version
project(YourProjectName VERSION 1.0 LANGUAGES CXX CUDA)

# Automatically detect GPU architecture of the build machine
set(CMAKE_CUDA_ARCHITECTURES 86)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories (optional but good practice)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include subdirectories
add_subdirectory(examples)
