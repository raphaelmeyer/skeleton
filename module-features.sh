#!/bin/bash

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

WIRE_SERVER=module/features/module-cucumber
NAME=wire-server

source ${PROJECT_ROOT}/env-amd64.sh

docker run -d -t --expose 3902 --name ${NAME} ${VOLUMES} ${CONTAINER} ${WIRE_SERVER}
docker run --rm -t --link ${NAME} -w ${SRC_GUEST}/module ${VOLUMES} ${CONTAINER} cucumber --tags @host $@

docker rm ${NAME}

