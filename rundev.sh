#!/usr/bin/env bash

NAME="dev"

# Check if --dev argument is passed
if [[ "$1" == "--dev" ]]; then
  IMAGE_NAME="shunya-dev:latest"
else
  IMAGE_NAME="vatsa821/shunya-dev:latest"
fi

USER=$(whoami)
HOME="${HOME:-/home/${USER}}"
CODEBASE_DIR="${CODEBASE_DIR:-${HOME}/shunya}"

# Adding the GPU flags
GPU_FLAGS="--gpus=all"

# Pull the latest version of the Docker image
if [[ "$1" != "--dev" ]]; then
  docker pull $IMAGE_NAME
fi

# Script to start the docker and attach the codebase to the container
docker run \
  $GPU_FLAGS \
  -it \
  --name $NAME \
  -h $NAME \
  -v "$CODEBASE_DIR:/shunya" \
  $IMAGE_NAME