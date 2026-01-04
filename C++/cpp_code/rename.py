#!/usr/bin/env python3
import os

def rename_files():
    cwd = os.getcwd()

    for filename in os.listdir(cwd):
        # Skip directories
        if not os.path.isfile(filename):
            continue

        # Apply transformations
        new_name = filename.replace("-", "_").lower()

        # Only rename if there is a change
        if new_name != filename:
            # Avoid overwriting existing files
            if os.path.exists(new_name):
                print(f"Skipping (target exists): {new_name}")
                continue

            os.rename(filename, new_name)
            print(f"Renamed: {filename} -> {new_name}")

if __name__ == "__main__":
    rename_files()
