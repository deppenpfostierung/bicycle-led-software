#!/bin/bash
# read in the .gitmodules file.
# replace all git@github.com:foo/bar with ../../foo/bar

# check if .gitmodules exists
if [[ ! -f ".gitmodules" ]]; then
    echo ".gitmodules file does not exist."
    exit 1
fi

# check if the operating system is macOS
if [[ "$(uname -s)" == "Darwin" ]]; then
    # use the macOS version of sed
    sed -i .bak 's|git@github.com:\(.*\)/\(.*\)|../../\1/\2|g' .gitmodules
    # remove the backup file created by sed
    rm .gitmodules.bak
else
    # use the GNU version of sed
    sed -i 's|git@github.com:\(.*\)/\(.*\)|../../\1/\2|g' .gitmodules
fi

echo "Replacement complete."