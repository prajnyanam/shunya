#!/usr/bin/env bash

NAME="dev"

# Check if the container is running
if [ "$(docker ps -a -q -f name=$NAME)" ]; then
    # Check if the container is running
    if [ "$(docker ps -q -f name=$NAME)" ]; then
        echo "Container $NAME is already running."

        # Prompt the user for action
        read -p "Do you want to (l)ogin to the existing container or (r)emove and restart it? (l/r): " choice

        case "$choice" in
            l|L )
                echo "Logging into the existing container: $NAME"
                docker exec -it $NAME /bin/bash  # or /bin/sh depending on your container's shell
                ;;
            r|R )
                echo "Stopping and removing the running container: $NAME"
                docker stop $NAME
                docker rm $NAME
                ;;
            * )
                echo "Invalid option. Please enter 'l' to login or 'r' to remove."
                ;;
        esac
    else
        echo "Container $NAME exists but is not running."

        # Prompt the user for action
        read -p "Do you want to (s)tart it or (r)emove it? (s/r): " choice

        case "$choice" in
            s|S )
                echo "Starting the container: $NAME"
                docker start $NAME
                echo "Logging into the container: $NAME"
                docker exec -it $NAME /bin/bash  # or /bin/sh depending on your container's shell
                ;;
            r|R )
                echo "Removing the container: $NAME"
                docker rm $NAME
                ;;
            * )
                echo "Invalid option. Please enter 's' to start or 'r' to remove."
                ;;
        esac
    fi
else
    echo "No existing container named $NAME found."
fi

# Check if --dev argument is passed
if [[ "$1" == "--dev" ]]; then
  IMAGE_NAME="shunya-dev:latest"
else
  IMAGE_NAME="vatsa821/shunya-dev:latest"
fi

USER=$(whoami)
HOME="${HOME:-/home/${USER}}"
CODEBASE_DIR="${CODEBASE_DIR:-${HOME}/shunya}"

# Do not change this, this is linked to the dockerfile name
DOCKER_USER="ian"

# Adding the GPU flags
GPU_FLAGS="--gpus=all"

# Pull the latest version of the Docker image
if [[ "$1" != "--dev" ]]; then
  docker pull $IMAGE_NAME
fi

# Mount gitconfig file
GIT_CONFIG_DIR="${HOME}/.gitconfig"
GIT_FLAGS="-v $GIT_CONFIG_DIR:/etc/gitconfig:ro"
SSH_FLAGS="-v $HOME/.ssh:/home/$DOCKER_USER/.ssh:ro"

# Script to start the docker and attach the codebase to the container
docker run \
  $GPU_FLAGS \
  -it \
  --name $NAME \
  -h $NAME \
  $GIT_FLAGS \
  $SSH_FLAGS \
  -v "$CODEBASE_DIR:/shunya" \
  $IMAGE_NAME