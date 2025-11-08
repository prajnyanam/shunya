#!/usr/bin/env bash

DEV_CONTAINER_SUFFIX="dev"
USER=$(whoami)
echo "USER: $USER"

# Create container name and sanitize it: replace invalid characters (characteres that are not letter or digits)
# with hyphens and convert to lowercase.
DEV_CONTAINER_NAME="${USER}_${DEV_CONTAINER_SUFFIX}"
DEV_CONTAINER_NAME="${DEV_CONTAINER_NAME//[^A-Za-z0-9_.-]/-}"
DEV_CONTAINER_NAME="$(echo "$DEV_CONTAINER_NAME" | tr '[:upper:]' '[:lower:]')"

# Usage function
DEV_ARG=false
ROOT_USER_ARG=false

# Parse arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        --dev)
            DEV_ARG=true
            shift
            ;;
        --root)
            ROOT_USER_ARG=true
            shift
            ;;
    esac
done

echo "DEV_ARG: $DEV_ARG"
echo "ROOT_USER_ARG: $ROOT_USER_ARG"

# Check if --dev argument is passed
if [ "$DEV_ARG" = true ]; then
  IMAGE_NAME="shunya-dev:latest"
else
  IMAGE_NAME="vatsa821/shunya-dev:latest"
fi

echo "IMAGE_NAME: $IMAGE_NAME"

ROOT_USER_FLAG=""
# Check if --root argument is passed
if [ "$ROOT_USER_ARG" = true ]; then
  ROOT_USER_FLAG="--user root"
fi

HOME="${HOME:-/home/${USER}}"
CODEBASE_DIR="${CODEBASE_DIR:-${HOME}/shunya}"

# Do not change this, this is linked to the dockerfile name
DOCKER_USER="ian"

# Adding the GPU flags
GPU_FLAGS="--gpus=all"

# Pull the latest version of the Docker image
if [ "$DEV_ARG" = !true ]; then
  docker pull $IMAGE_NAME
fi

# Mount gitconfig file
GIT_CONFIG_DIR="${HOME}/.gitconfig"
GIT_FLAGS="-v $GIT_CONFIG_DIR:/etc/gitconfig:ro"
# Mount ssh keys base on user 
if [ "$ROOT_USER_ARG" = true ]; then
  SSH_FLAGS="-v $HOME/.ssh:/root/.ssh:ro"
else
  SSH_FLAGS="-v $HOME/.ssh:/home/$DOCKER_USER/.ssh:ro"
fi

# allows local root users (like Docker containers) to connect to display.
xhost +local:root

# Set the DISPLAY_FLAG
DISPLAY_FLAGS="-e DISPLAY=$DISPLAY \
               -v /tmp/.X11-unix:/tmp/.X11-unix"

# Script to start the docker and attach the codebase to the container
docker run \
  $ROOT_USER_FLAG \
  $GPU_FLAGS \
  $DISPLAY_FLAGS \
  -it \
  -d \
  --name $DEV_CONTAINER_NAME \
  -h $DEV_CONTAINER_NAME \
  $GIT_FLAGS \
  $SSH_FLAGS \
  -v "$CODEBASE_DIR:/shunya" \
  $IMAGE_NAME

# Attach current terminal to the container
docker exec -it $DEV_CONTAINER_NAME /bin/bash
