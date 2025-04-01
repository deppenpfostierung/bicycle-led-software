#!/bin/bash

# run clang-format on all .h and .cpp files in the ./main directory.
# exclude the ./main/icons directory.

# check if clang-format is installed
if ! command -v clang-format &> /dev/null; then
    echo "clang-format could not be found, please install it."
    exit 1
fi

# check if ./main/ exists
if [[ ! -d "./main" ]]; then
    echo "Directory ./main/ does not exist."
    exit 1
fi

echo "Running clang-format on all .h and .cpp files in the ./main directory, excluding the ./main/icons directory."

# run clang-format. use the '.clang-format' file in the current directory.
find ./main -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' | \
    grep -v './main/icons/' | \
    xargs clang-format --Werror --verbose --style=file -i