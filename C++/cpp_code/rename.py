# #!/usr/bin/env python3
# import os
#
# def rename_files():
#     cwd = os.getcwd()
#
#     for filename in os.listdir(cwd):
#         # Skip directories
#         if not os.path.isfile(filename):
#             continue
#
#         # Apply transformations
#         new_name = filename.replace("-", "_").lower()
#
#         # Only rename if there is a change
#         if new_name != filename:
#             # Avoid overwriting existing files
#             if os.path.exists(new_name):
#                 print(f"Skipping (target exists): {new_name}")
#                 continue
#
#             os.rename(filename, new_name)
#             print(f"Renamed: {filename} -> {new_name}")
#
# if __name__ == "__main__":
#     rename_files()


#!/usr/bin/env python3
#!/usr/bin/env python3
import os
import sys
import tempfile

def rename_to_lowercase(dry_run=True):
    """
    Rename all files in the current directory to lowercase.
    Handles case-insensitive filesystems by using temporary names.

    Args:
        dry_run: If True, only show what would be renamed without actually renaming
    """
    current_dir = os.getcwd()
    print(f"Working directory: {current_dir}\n")

    files = [f for f in os.listdir('.') if os.path.isfile(f)]

    if not files:
        print("No files found in current directory.")
        return

    renamed_count = 0
    skipped_count = 0

    for filename in files:
        # Skip the script itself
        if filename == os.path.basename(__file__):
            continue

        new_filename = filename.lower()

        # Skip if already lowercase
        if filename == new_filename:
            skipped_count += 1
            continue

        if dry_run:
            print(f"Would rename: '{filename}' -> '{new_filename}'")
        else:
            try:
                # Use a temporary name to handle case-insensitive filesystems
                # where 'File.txt' and 'file.txt' are the same file
                temp_name = f"_temp_{os.getpid()}_{filename}"

                # Rename to temp, then to final lowercase name
                os.rename(filename, temp_name)
                os.rename(temp_name, new_filename)

                print(f"✓ Renamed: '{filename}' -> '{new_filename}'")
                renamed_count += 1
            except Exception as e:
                print(f"✗ Error renaming '{filename}': {e}")
                skipped_count += 1
                # Try to restore from temp if it exists
                if os.path.exists(temp_name):
                    try:
                        os.rename(temp_name, filename)
                    except:
                        pass

    print(f"\n{'[DRY RUN] ' if dry_run else ''}Summary:")
    files_to_rename = len([f for f in files if f.lower() != f and f != os.path.basename(__file__)])
    print(f"  Files {'would be' if dry_run else ''} renamed: {files_to_rename if dry_run else renamed_count}")
    print(f"  Files skipped: {skipped_count}")

if __name__ == "__main__":
    print("=== Lowercase Filename Converter ===\n")

    # First, run in dry-run mode to show what would happen
    rename_to_lowercase(dry_run=True)

    print("\n" + "="*50)
    response = input("\nProceed with renaming? (yes/no): ").strip().lower()

    if response in ['yes', 'y']:
        print("\nProceeding with rename...\n")
        rename_to_lowercase(dry_run=False)
    else:
        print("\nOperation cancelled.")