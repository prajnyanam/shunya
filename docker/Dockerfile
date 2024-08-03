# Use the specified NVIDIA CUDA base image
FROM nvidia/cuda:11.8.0-devel-ubuntu22.04

# Set the working directory
WORKDIR /shunya

# Install basic dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    unzip \
    curl \
    software-properties-common \
    python3.10 \
    python3-pip \
    libgl1-mesa-glx \
    bash-completion \
    vim

# Install bazel
RUN wget --no-verbose --read-timeout 1000 https://github.com/bazelbuild/bazel/releases/download/6.5.0/bazel_6.5.0-linux-x86_64.deb \
  && dpkg -i bazel_6.5.0-linux-x86_64.deb \
  && rm bazel_6.5.0-linux-x86_64.deb

# Install python requirements
COPY requirements/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

ARG USER=ian
ARG GROUP=prajnyanam

# Creates a group with a specified GID. Creates a user with a specified UID, adds them to the group, 
# sets their home directory, shell, and disables their password. Grants the user sudo privileges by adding them to the sudo group.
# Configures passwordless sudo for the user by appending a rule to the sudoers file.
RUN addgroup --gid 1000 $GROUP \
  && adduser --uid 1000 --ingroup $GROUP --home /home/$USER --shell /bin/bash --disabled-password --gecos "" $USER \
  && adduser $USER sudo

USER $USER:$GROUP

CMD ["/bin/bash"]
