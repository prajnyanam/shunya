cmake_minimum_required(VERSION 3.16)

# Project name and version
project(shunya VERSION 1.0 LANGUAGES CXX CUDA)

# Automatically detect GPU architecture of the build machine
set(CMAKE_CUDA_ARCHITECTURES 86)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Generates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories (optional but good practice)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ROS 2 dependencies, ament_cmake must be defined first
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Include subdirectories
add_subdirectory(examples)

# Install launch/config/resource files, Places binaries and launch files into the correct share/lib directories so ros2 run and ros2 launch work.
install(DIRECTORY launch
        DESTINATION share/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.py")

# ament footer (MUST be last)
ament_package()
