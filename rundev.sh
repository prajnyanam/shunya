#!/usr/bin/env bash

NAME="dev"

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

USER=$(whoami)

echo "USER: $USER"

HOME="${HOME:-/home/${USER}}"
CODEBASE_DIR="${CODEBASE_DIR:-${HOME}/shunya}"

# Do not change this, this is linked to the dockerfile name
DOCKER_USER="ian"

# Adding the GPU flags
GPU_FLAGS="--gpus=all"

# Pull the latest version of the Docker image
if [ "$ROOT_USER_FLAG" = true ]; then
  docker pull $IMAGE_NAME
fi

# Mount gitconfig file
GIT_CONFIG_DIR="${HOME}/.gitconfig"
GIT_FLAGS="-v $GIT_CONFIG_DIR:/etc/gitconfig:ro"
SSH_FLAGS="-v $HOME/.ssh:/home/$DOCKER_USER/.ssh:ro"

# Script to start the docker and attach the codebase to the container
docker run \
  $ROOT_USER_FLAG \
  $GPU_FLAGS \
  -d \
  -it \
  --name $NAME \
  -h $NAME \
  $GIT_FLAGS \
  $SSH_FLAGS \
  -v "$CODEBASE_DIR:/shunya" \
  $IMAGE_NAME
