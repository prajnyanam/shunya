# Use the specified NVIDIA CUDA base image
FROM nvidia/cuda:11.8.0-base-ubuntu22.04

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
    python3-pip

# Install bazel
RUN wget --no-verbose --read-timeout 1000 https://github.com/bazelbuild/bazel/releases/download/6.5.0/bazel_6.5.0-linux-x86_64.deb \
  && dpkg -i bazel_6.5.0-linux-x86_64.deb \
  && rm bazel_6.5.0-linux-x86_64.deb

# Set up entrypoint
CMD ["/bin/bash"]