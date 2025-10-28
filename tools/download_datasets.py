#!/usr/bin/env python3

import gdown
import zipfile
from pathlib import Path
import os

DATASET_PATH = Path("/mnt/datasets")

def download_visnav_dataset():
    download_output = DATASET_PATH / "visnav_dataset.zip"
    extract_path = DATASET_PATH / "vis_nav"

    if extract_path.exists():
        print(f"VisNav dataset already exists at {extract_path}. Skipping download.")
        return

    if not download_output.exists():
        print("Starting vis nav dataset download...")
        url = "https://drive.google.com/uc?id=16tY7tPZiNIoyAhknvyXnp0jAfccIcHtL"
        gdown.download(url, str(download_output), use_cookies=False, quiet=False)
        print(f'Downloaded VisNav dataset to {download_output}, Extracting the dataset...')
    
    os.makedirs(extract_path, exist_ok=True)

    with zipfile.ZipFile(download_output, 'r') as zip_ref:
        zip_ref.extractall(extract_path)
    print(f'Extracted dataset to {extract_path}, Removing the zip file...')

    os.remove(download_output)
    print(f'Done...')

def main():
    download_visnav_dataset()

if __name__ == '__main__':
    main()