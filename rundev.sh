#!/usr/bin/env bash

NAME="dev"

IMAGE_NAME="vatsa821/shunya-dev:latest"

USER=$(whoami)
HOME="${HOME:-/home/${USER}}"
CODEBASE_DIR="${CODEBASE_DIR:-${HOME}/shunya}"

# Pull the latest version of the Docker image
docker pull $IMAGE_NAME

# Script to start the docker and attach the codebase to the container
docker run \
  -it --rm \
  --name $NAME \
  -h $NAME \
  -v "$CODEBASE_DIR:/shunya" \
  $IMAGE_NAME