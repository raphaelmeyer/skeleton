#!/bin/bash

AMD64=1.0.0

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SRC_HOST=${PROJECT_ROOT}/source
SRC_GUEST=/home/user/src

VOLUMES="--volumes-from amd64-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro"
CONTAINER="raphaelmeyer/amd64-sdk:${AMD64}"

