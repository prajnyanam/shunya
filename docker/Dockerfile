# Use the specified NVIDIA CUDA base image
FROM nvidia/cuda:11.8.0-devel-ubuntu22.04

ENV DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC

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
    vim \
    tmux \
    clang-tidy \
    clang-format

# Install ROS2 and colcon
RUN add-apt-repository universe && \
    apt-get update && \
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" > /etc/apt/sources.list.d/ros2.list && \
    apt-get update && \
    apt-get install -y \
    ros-humble-desktop \
    python3-colcon-common-extensions

# Source ROS2 setup script, this adds to all the users
RUN echo "source /opt/ros/humble/setup.bash" >> /etc/bash.bashrc

# Clean up
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Clone and build Catch2
RUN git clone https://github.com/catchorg/Catch2.git && \
    cd Catch2 && \
    cmake -B build -S . -DBUILD_TESTING=OFF && \
    cmake --build build/ --target install && \
    cd .. && rm -rf Catch2

# Install python requirements
COPY --chown=root:root requirements/requirements.txt /tmp/requirements.txt
RUN pip install --no-cache-dir -r /tmp/requirements.txt && rm -f /tmp/requirements.txt

# Enable autocomplete in Bash for all users
RUN curl -o /etc/bash_completion.d/git-completion.bash \
      https://raw.githubusercontent.com/git/git/master/contrib/completion/git-completion.bash && \
    echo "source /etc/bash_completion.d/git-completion.bash" >> /etc/bash.bashrc

# Add safe directory for git to avoid dubious ownership warnings
RUN git config --global --add safe.directory /shunya

ARG USERNAME=ian
ARG GROUPNAME=prajnyanam
# Note: we do NOT bake fixed IDs. CI/hosts should override with: --user "$(id -u):$(id -g)"
# Do NOT switch USER here; keep root as default for maximum portability in CI.
# In local dev you can still run as the created user:
#   docker run --user "${USERNAME}" ...
# In CI prefer host-matched IDs:
#   docker run --user "$(id -u):$(id -g)" $(for g in $(id -G); do printf -- "--group-add %s " "$g"; done) ...
RUN groupadd -r "${GROUPNAME}" && useradd -m -r -g "${GROUPNAME}" -s /bin/bash "${USERNAME}"

CMD ["/bin/bash"]
