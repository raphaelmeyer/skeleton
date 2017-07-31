#!/bin/bash

YBPI=2.3.0

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SRC_HOST=${PROJECT_ROOT}/source
SRC_GUEST=/home/user/src

VOLUMES="--volumes-from ybpi-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro"
CONTAINER="raphaelmeyer/ybpi-sdk:${YBPI}"

