#!/bin/bash

# converts images from ./icons/* to ./main/icons/*.h/*.cpp

FORCE_PULL=false

# handle args if any
while getopts ":f" opt; do
    case $opt in
        f)
            FORCE_PULL=true
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done

# check if docker image is pulled
DOCKER_IMAGE="ghcr.io/commanderredyt/rgb565-converter:latest"

# check if docker is running
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

# check if ./icons/ exists
if [[ ! -d "./icons" ]]; then
    echo "Directory ./icons/ does not exist."
    exit 1
fi

mkdir -p ./main/icons

# check if ./main/icons/ exists
if [[ ! -d "./main/icons" ]]; then
    echo "Directory ./main/icons/ does not exist."
    exit 1
fi

for icon in ./icons/*; do
    if [[ -f "$icon" ]]; then
        filename=$(basename "$icon")
        filename_no_ext="${filename%.*}"
        echo "Converting $filename to $filename_no_ext.h and $filename_no_ext.cpp"
        docker run --rm -v "$(pwd):/data" $DOCKER_IMAGE -i "$icon" -o "/data/main/icons/$filename_no_ext.cpp" --swap
    fi
done