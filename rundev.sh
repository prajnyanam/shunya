#!/usr/bin/env bash

DEV_CONTAINER_SUFFIX="dev"
HOST_USER=$(whoami)
echo "USER: $HOST_USER"

# Create container name and sanitize it: replace invalid characters (characteres that are not letter or digits)
# with hyphens and convert to lowercase.
DEV_CONTAINER_NAME="${HOST_USER}_${DEV_CONTAINER_SUFFIX}"
DEV_CONTAINER_NAME="${DEV_CONTAINER_NAME//[^A-Za-z0-9_.-]/-}"
DEV_CONTAINER_NAME="$(echo "$DEV_CONTAINER_NAME" | tr '[:upper:]' '[:lower:]')"

HOST_HOME="${HOME:-/home/${HOST_USER}}"
DATA_DIR="${HOST_HOME}/data"
DATASET_DIR="/mnt/datasets"
CODEBASE_DIR="${CODEBASE_DIR:-${HOST_HOME}/shunya}"

# Usage function
DEV_ARG=false
ROOT_USER_ARG=false

# Basic Checks
if [ ! -d "$DATA_DIR" ]; then
    echo "❌ Error: Data directory '$DATA_DIR' does not exist."
    echo "👉 Please create it using: mkdir -p \"$DATA_DIR\""
    exit 1
fi
if [ ! -d "$DATASET_DIR" ]; then
    echo "❌ Error: Data directory '$DATASET_DIR' does not exist."
    echo "👉 Please create it using: mkdir -p \"$DATASET_DIR\""
    exit 1
fi

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

# Pull the latest version (only for non-dev)
if [ "$DEV_ARG" != true ]; then
  docker pull "$IMAGE_NAME"
fi

# User / groups
USER_FLAGS=""
GROUP_FLAGS=""
ROOT_USER_FLAG=""
if [ "$ROOT_USER_ARG" = true ]; then
  ROOT_USER_FLAG="--user root"
else
  # Match host UID:GID
  USER_FLAGS="--user $(id -u):$(id -g)"
  # Add all host groups
  GROUP_FLAGS="$(for g in $(id -G); do printf -- '--group-add %s ' "$g"; done)"
fi

NAME_RES_FLAGS="-v /etc/passwd:/etc/passwd:ro -v /etc/group:/etc/group:ro"

# Adding the GPU flags
GPU_FLAGS="--gpus=all"

# Mount the data directory
DATA_DIR_MOUNTING_FLAG="-v ${DATA_DIR}:/data:rw"
DATASET_DIR_MOUNTING_FLAG="-v ${DATASET_DIR}:${DATASET_DIR}:rw"

# Pull the latest version of the Docker image
if [ "$DEV_ARG" != true ]; then
  docker pull $IMAGE_NAME
fi

# Mount gitconfig file
GIT_CONFIG_FILE="${HOST_HOME}/.gitconfig"
GIT_FLAGS=""
if [ -f "$GIT_CONFIG_FILE" ]; then
  GIT_FLAGS="-v ${GIT_CONFIG_FILE}:/etc/gitconfig:ro"
fi

# Mount ssh keys base on user 
SSH_FLAGS=""
if [ -d "${HOST_HOME}/.ssh" ]; then
  if [ "$ROOT_USER_ARG" = true ]; then
    SSH_FLAGS="-v ${HOST_HOME}/.ssh:/root/.ssh:ro"
  else
    SSH_FLAGS="-v ${HOST_HOME}/.ssh:${HOST_HOME}/.ssh:ro"
  fi
fi

CODEBASE_MOUNTING_FLAG="-v ${CODEBASE_DIR}:/shunya"

# allows local root users (like Docker containers) to connect to display.
xhost +local:root

# Set the DISPLAY_FLAG
DISPLAY_FLAGS="-e DISPLAY=$DISPLAY \
               -v /tmp/.X11-unix:/tmp/.X11-unix"

# Script to start the docker and attach the codebase to the container
docker run \
  -it -d \
  --name "$DEV_CONTAINER_NAME" \
  -h "$DEV_CONTAINER_NAME" \
  $ROOT_USER_FLAG \
  $USER_FLAGS \
  $GROUP_FLAGS \
  $GPU_FLAGS \
  $DISPLAY_FLAGS \
  $GIT_FLAGS \
  $SSH_FLAGS \
  $DATA_DIR_MOUNTING_FLAG \
  $DATASET_DIR_MOUNTING_FLAG \
  $CODEBASE_MOUNTING_FLAG \
  $NAME_RES_FLAGS \
  "$IMAGE_NAME"

# Attach current terminal to the container
docker exec -it $DEV_CONTAINER_NAME /bin/bash
