
cmake_minimum_required(VERSION 3.16)

# Project name and version
project(shunya_examples VERSION 1.0 LANGUAGES CXX CUDA)

get_filename_component(SHUNYA_WORKSPACE_DIR "${CMAKE_SOURCE_DIR}/../.." ABSOLUTE)
set(SHUNYA_CMAKE_TEMPLATES_DIR ${SHUNYA_WORKSPACE_DIR}/cmake)
message(STATUS "SHUNYA_WORKSPACE_DIR: ${SHUNYA_WORKSPACE_DIR}")
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
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# ROS 2 dependencies, ament_cmake must be defined first
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Include subdirectories
add_subdirectory(basic)
add_subdirectory(cuda)
add_subdirectory(tests)

# Install launch/config/resource files, Places binaries and launch files into the correct share/lib directories so ros2 run and ros2 launch work.
install(DIRECTORY launch
        DESTINATION share/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.py")

# ament footer (MUST be last)
ament_package()
