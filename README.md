# Installation and Development Instructions

## Installation Instructions

1. **Install Docker**
   - Follow the [Docker installation guide for Ubuntu](https://docs.docker.com/engine/install/ubuntu/) to install Docker on your system.

2. **Add Docker as a Non-Root User**
   - To run Docker commands without `sudo`, add your user to the `docker` group. Instructions can be found [here](https://docs.docker.com/engine/install/linux-postinstall/).

3. **Reboot Your System**
   - Apply the group changes by rebooting your system:
     ```bash
     sudo reboot
     ```

4. **Install the NVIDIA Driver**
   - Ensure the NVIDIA driver is installed. You can verify its installation by running:
     ```bash
     nvidia-smi
     ```

5. **Install the NVIDIA Container Toolkit**
   - Follow the instructions in the [NVIDIA Container Toolkit installation guide](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html) to set up the toolkit.

## Development Instructions

1. **Prepare the Development Environment**
   - Make the `rundev.sh` script executable:
     ```bash
     chmod +x rundev.sh
     ```

2. **Run the Development Environment**
   - Execute the `rundev.sh` script to start the development environment:
     ```bash
     ./rundev.sh
     ```

3. **Verify NVIDIA Integration**
   - Check that you can run `nvidia-smi` inside the Docker container to confirm that the NVIDIA setup is working correctly.
