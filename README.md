## Installation Instructions

1. **Install Docker**
   - Follow the instructions in the [Docker installation guide for Ubuntu](https://docs.docker.com/engine/install/ubuntu/).

2. **Add Docker as a Non-Root User**
   - After installing Docker, ensure you can run Docker commands without `sudo` by adding your user to the `docker` group. Follow the instructions [here](https://docs.docker.com/engine/install/linux-postinstall/).

3. **Reboot**
   - To apply the group changes, reboot your system:
     ```bash
     sudo reboot
     ```