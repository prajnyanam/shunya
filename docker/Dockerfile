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
    vim \
    tmux \
    clang-tidy \
    clang-format

# Clone and build Catch2
RUN git clone https://github.com/catchorg/Catch2.git && \
    cd Catch2 && \
    cmake -B build -S . -DBUILD_TESTING=OFF && \
    cmake --build build/ --target install && \
    cd .. && rm -rf Catch2

# Install python requirements
COPY requirements/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Download Git autocomplete script
RUN curl -o /etc/bash_completion.d/git-completion.bash https://raw.githubusercontent.com/git/git/master/contrib/completion/git-completion.bash

# Enable autocomplete in Bash for all users
RUN echo "source /etc/bash_completion.d/git-completion.bash" >> /etc/bash.bashrc

# Add safe directory for git to avoid dubious ownership warnings
RUN git config --global --add safe.directory /shunya


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
