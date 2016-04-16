#!/bin/bash

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source ${PROJECT_ROOT}/env-amd64.sh

docker run --rm -t -w ${SRC_GUEST}/module ${VOLUMES} ${CONTAINER} cucumber --tags @target $@

