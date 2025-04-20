# !/bin/bash
# This script checks the code style of C++ files in the project using clang-format.
# It formats the files in place if they do not conform to the style.

# Check if there are any uncommitted changes
if ! git diff-index --quiet HEAD --; then
  echo "There are uncommitted changes. Please commit or stash them before running this script."
  exit 1
fi

find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.h" \) \
  -not -path "./build/*" \
  -exec clang-format -i {} +