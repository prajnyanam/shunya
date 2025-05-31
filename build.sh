#!/bin/bash

set -e  # Exit immediately on error

# Navigate to shunya directory
cd /shunya

# Building using ROS2
colcon build --symlink-install --cmake-args -DENABLE_CLANG_FORMAT=ON -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE

source install/setup.bash

echo "✅ Build complete!"