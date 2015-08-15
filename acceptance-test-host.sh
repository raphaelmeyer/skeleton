#!/bin/bash

HOST=0.1.0

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SRC_HOST=${PROJECT_ROOT}/source
SRC_GUEST=/home/user/src

docker run -d -t --volumes-from host-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro --expose 3902 --name wire-server host-gcc:${HOST} /workspace/acceptance-test-host/acceptance-test-host

docker run --rm -t --volumes-from host-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro --link wire-server -w ${SRC_GUEST} host-gcc:${HOST} cucumber

docker rm wire-server

