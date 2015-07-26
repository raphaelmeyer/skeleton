#!/bin/bash

SRC_HOST=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SRC_GUEST=/home/user/src

docker run --rm -t --volumes-from host-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro host-gcc cmake ${SRC_GUEST}
docker run --rm -t --volumes-from host-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro host-gcc cmake --build .

