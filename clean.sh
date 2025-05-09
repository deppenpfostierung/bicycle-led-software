#!/bin/bash

# read the symlink of build/
if [ -L build ]; then
    # read the symlink
    link=$(readlink build)
    # remove the symlink
    rm -rf build build_*

    # run switchconf with "build_<name>" as argument
    config_name=$(basename "$link" | cut -d'_' -f2-)
    echo "switching to $config_name"

    ./switchconf.sh "$config_name"
else
  echo "build is not a symlink, aborting"
  exit 1
fi