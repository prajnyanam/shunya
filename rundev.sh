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

# Function to prompt user for confirmation
prompt_user() {
  read -p "$1 (y/n): " choice
  case "$choice" in
    y|Y ) return 0 ;;
    n|N ) return 1 ;;
    * ) echo "Invalid input. Please enter 'y' or 'n'."; prompt_user "$1" ;;
  esac
}

# Get the remote image digest without pulling the image
get_remote_image_digest() {
  docker pull --quiet $IMAGE_NAME > /dev/null
  remote_digest=$(docker inspect --format='{{index .RepoDigests 0}}' $IMAGE_NAME)
  echo "${remote_digest##*@}"
}

# Get the local image digest
get_local_image_digest() {
  local_digest=$(docker inspect --format='{{index .RepoDigests 0}}' $IMAGE_NAME)
  echo "${local_digest##*@}"
}

if [[ "$1" != "--dev" ]]; then
  remote_digest=$(get_remote_image_digest)
  local_digest=$(get_local_image_digest)

  if [[ "$remote_digest" != "$local_digest" ]]; then
    echo "A new version of the Docker image is available."
    if prompt_user "Do you want to pull the new image and spawn a new container?"; then
      docker pull $IMAGE_NAME

      # Check if the container is already running
      if docker ps -a --format '{{.Names}}' | grep -Eq "^${NAME}\$"; then
        # Prompt to remove the existing container
        if prompt_user "Do you want to remove the existing container?"; then
          docker stop $NAME
          docker rm $NAME
          echo "Existing container removed."
        else
          echo "Continuing with the existing container."
        fi
      fi

    else
      echo "Continuing with the existing image."
    fi
  else
    echo "The local image is up to date."
  fi
fi

# Check if the container is already running
if docker ps -a --format '{{.Names}}' | grep -Eq "^${NAME}\$"; then
  # If the container is not running, start it
  if [[ "$(docker inspect -f '{{.State.Running}}' ${NAME})" == "false" ]]; then
    docker start $NAME
  fi
  # Attach to the running container
  echo "Attaching to the running container"
  docker exec -it $NAME bash

else
  echo "Running a new container"
  # Run a new container

  # DOCKER RUN COMMAND :
  # -it : interactive terminal
  # --name : name of the container
  # -h : hostname of the container
  # -v : mount the codebase directory
  # -w : working directory
  # --privileged : give extended privileges to the container
  # --network host : use the host's network stack inside the container
  # --env="DISPLAY" : pass the DISPLAY
  # --env="QT_X11_NO_MITSHM=1" : pass the QT_X11_NO_MITSHM
  # --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" : mount the X11 socket
  # -d : run the container in the background (detach)
 
  docker run \
    $GPU_FLAGS \
    -it \
    --name $NAME \
    -h $NAME \
    -v "$CODEBASE_DIR:/shunya:rw" \
    -w "/shunya" \
    -d \
    --privileged --network host --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1"   \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    $IMAGE_NAME
fi

if prompt_user "Do you want to remove the existing container?"; then
  echo "Removing the existing container."
  docker stop $NAME
  docker rm $NAME
  echo "Existing container removed."
fi