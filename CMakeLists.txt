cmake_minimum_required(VERSION 3.16)

# Project name and version
project(shunya VERSION 1.0 LANGUAGES CXX CUDA)

set(SHUNYA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SHUNYA_CMAKE_TEMPLATES_DIR ${SHUNYA_SOURCE_DIR}/cmake)
message(STATUS "SHUNYA_SOURCE_DIR: ${SHUNYA_SOURCE_DIR}")
message(STATUS "SHUNYA_CMAKE_TEMPLATES_DIR: ${SHUNYA_CMAKE_TEMPLATES_DIR}")

#-------------------------------------------------------------------------------------------------
# Helper scripts to configure shunya build

include(${SHUNYA_CMAKE_TEMPLATES_DIR}/code_formatting_options.cmake)  # configure code auto-formatting tools

#-------------------------------------------------------------------------------------------------

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
