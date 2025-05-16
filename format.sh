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

# print clang-format version
clang_format_version=$(clang-format --version) # "clang-format version x.y.z"
clang_format_command="clang-format"

# check if clang-format version is 19 or higher
if [[ $clang_format_version =~ [0-9]+ ]]; then
    clang_format_version_number=${BASH_REMATCH[0]}
    if (( clang_format_version_number < 19 )); then
        # check if clang-format-19 is installed
        if ! command -v clang-format-19 &> /dev/null; then
            echo "clang-format version $clang_format_version_number is less than 19 and clang-format-19 is not installed."
            exit 1
        else
            echo "clang-format version $clang_format_version_number is less than 19, using clang-format-19."
            clang_format_command="clang-format-19"
        fi
    fi
fi

echo "Running $(which $clang_format_command) on all .h and .cpp files in the ./main directory, excluding the ./main/icons directory."

# run clang-format. use the '.clang-format' file in the current directory.
find ./main -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' | \
    grep -v './main/icons/' | \
    xargs $clang_format_command --Werror --verbose --style=file -i