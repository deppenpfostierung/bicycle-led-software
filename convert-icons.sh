#!/bin/bash

# converts images from ./icons/* to ./main/icons/*.h/*.cpp

FORCE_PULL=false
NEEDS_DOCKER=false
DISABLE_DOCKER=true

BACKGROUND="#3c3c3c"

OUTPUT_DIR="./main/icons"

# if not linux, use docker
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    NEEDS_DOCKER=true
    echo "This script is designed to run on Linux. All other platforms will use Docker."
    echo "Please make sure Docker is installed and running."
fi

# handle args if any
while getopts ":fo:" opt; do
    case $opt in
        f)
            FORCE_PULL=true
            ;;

        o)
            OUTPUT_DIR=$OPTARG
            ;;

        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done

# if OUTPUT_DIR is empty, exit
if [[ -z "$OUTPUT_DIR" ]]; then
    echo "ERROR: Output directory is empty."
    exit 1
fi

# check if docker image is pulled
DOCKER_IMAGE="ghcr.io/commanderredyt/rgb565-converter:latest"

# check if docker is running
if [[ "$NEEDS_DOCKER" == true ]]; then
  if ! docker info > /dev/null 2>&1; then
      echo "Docker is not running, please start Docker."
      exit 1
  fi

  if [[ "$(docker images -q $DOCKER_IMAGE 2> /dev/null)" == "" ]]; then
      echo "Docker image not found, pulling..."
      docker pull $DOCKER_IMAGE
  fi

  # check if docker image is up to date
  if [[ "$FORCE_PULL" == true ]]; then
      echo "Force pulling docker image..."
      docker pull $DOCKER_IMAGE
  fi

  # check if docker image works
  if ! docker run --rm $DOCKER_IMAGE --help > /dev/null 2>&1; then
      echo "Docker image is not working, please check the image."
      exit 1
  fi
else
  # check if rgb565-converter is installed
  if ! command -v rgb565-converter &> /dev/null; then
      echo "rgb565-converter could not be found, please install it."
      # check if pacman is installed
      if command -v pacman &> /dev/null; then
          echo "Please install rgb565-converter from the AUR"
      else
          echo "Please install rgb565-converter from here: https://github.com/CommanderRedYT/rgb565-converter"
      fi
      exit 1
  fi

  # check if rgb565-converter works
  if ! rgb565-converter --help > /dev/null 2>&1; then
      echo "rgb565-converter is not working, please check the installation."
      exit 1
  fi
fi

# check if ./icons/ exists
if [[ ! -d "./icons" ]]; then
    echo "Directory ./icons/ does not exist."
    exit 1
fi

mkdir -p "$OUTPUT_DIR"

if [[ ! -d "$OUTPUT_DIR" ]]; then
    echo "Directory $OUTPUT_DIR does not exist."
    exit 1
fi

# if docker is disabled, exit
if [[ "$DISABLE_DOCKER" == true && "$NEEDS_DOCKER" == true ]]; then
    echo "Docker usage is not tested and will most likely fail. Do not use it."
    exit 1
fi

for icon in ./icons/*; do
    if [[ -f "$icon" ]]; then
        filename=$(basename "$icon")
        filename_no_ext="${filename%.*}"
        echo "Converting $filename to $filename_no_ext.h and $filename_no_ext.cpp"
        if [[ "$NEEDS_DOCKER" == true ]]; then
            docker run --rm -v "$(pwd):/data" $DOCKER_IMAGE -i "$icon" -o "/data/$OUTPUT_DIR/$filename_no_ext.cpp" --swap
            docker run --rm -v "$(pwd):/data" $DOCKER_IMAGE -i "$icon" -o "/data/$OUTPUT_DIR/${filename_no_ext}_grey.cpp" --swap --background "$BACKGROUND"
        else
            rgb565-converter -i "$icon" -o "$OUTPUT_DIR/$filename_no_ext.cpp" --swap
            rgb565-converter -i "$icon" -o "$OUTPUT_DIR/${filename_no_ext}_grey.cpp" --swap --background "$BACKGROUND"
        fi
    fi
done