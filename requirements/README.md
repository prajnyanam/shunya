## Installing a new python package

1. Get into the docker:
    ```bash
    ./rundev.sh
    ```

2. Run pip-compile and generate the `requirements.txt`
    ```bash
    HOME=/tmp/pip-cache pip-compile requirements/requirements.in --output-file=requirements/requirements.txt
    ```

3. Re-Build the docker:

    ```bash
    ./docker/build.sh
    ```