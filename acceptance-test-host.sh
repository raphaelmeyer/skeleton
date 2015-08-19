#!/bin/bash

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source ${PROJECT_ROOT}/env-host.sh

docker run -d -t --expose 3902 --name wire-server ${VOLUMES} ${CONTAINER} acceptance-test-host/acceptance-test-host
docker run --rm -t --link wire-server -w ${SRC_GUEST} ${VOLUMES} ${CONTAINER} cucumber

docker rm wire-server

