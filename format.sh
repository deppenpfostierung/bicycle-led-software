#!/bin/bash

# run clang-format on all .h and .cpp files in the ./main directory.
# exclude the ./main/icons directory.
MINIMUM_CLANG_FORMAT_VERSION=19

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
    if (( clang_format_version_number < MINIMUM_CLANG_FORMAT_VERSION )); then
        # check if clang-format-$MINIMUM_CLANG_FORMAT_VERSION
        if ! command -v clang-format-$MINIMUM_CLANG_FORMAT_VERSION &> /dev/null; then
            echo "Default $(which clang-format) version $clang_format_version_number is less than $MINIMUM_CLANG_FORMAT_VERSION and clang-format-$MINIMUM_CLANG_FORMAT_VERSION is not installed."
            exit 1
        else
            echo "Default $(which clang-format) version $clang_format_version_number is less than $MINIMUM_CLANG_FORMAT_VERSION, using clang-format-$MINIMUM_CLANG_FORMAT_VERSION instead."
            clang_format_command="clang-format-$MINIMUM_CLANG_FORMAT_VERSION"
        fi
    fi
fi

echo "Running $(which $clang_format_command) on all .h and .cpp files in the ./main directory, excluding the ./main/icons directory."

# run clang-format. use the '.clang-format' file in the current directory.
find ./main -iname '*.h' -o -iname '*.cpp' -o -iname '*.c' | \
    grep -v './main/icons/' | \
    xargs $clang_format_command --Werror --verbose --style=file -i