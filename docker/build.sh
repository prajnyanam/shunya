#!/bin/bash
set -e

# Check if the script is being run from the root folder (check for docker/Dockerfile)
if [ ! -f "docker/Dockerfile" ]; then
    echo "Error: Dockerfile not found in docker/ folder. Please run this script from the root of the repository."
    exit 1
fi

# Build the Docker image
echo "Building the Docker image..."
docker build -f docker/Dockerfile -t shunya-dev .

echo "Docker image built successfully."
