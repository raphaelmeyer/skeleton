#!/bin/bash

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

WIRE_SERVER=controller/features/controller-cucumber
NAME=wire-server

source ${PROJECT_ROOT}/env-amd64.sh

docker run -d -t --expose 3902 --name ${NAME} ${VOLUMES} ${CONTAINER} ${WIRE_SERVER}
docker run --rm -t --link ${NAME} -w ${SRC_GUEST}/controller ${VOLUMES} ${CONTAINER} cucumber $@

docker rm ${NAME}

