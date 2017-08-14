#!/bin/bash

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PROJECT_ROOT=$( cd "${SCRIPT_DIR}/.." && pwd )

WIRE_SERVER=module/features/module-cucumber
NAME=wire-server

source ${SCRIPT_DIR}/env-amd64.sh

cd ${PROJECT_ROOT}

docker run -d -t --expose 3902 --name ${NAME} ${VOLUMES} ${CONTAINER} ${WIRE_SERVER}
docker run --rm -t --link ${NAME} -w ${SRC_GUEST}/module ${VOLUMES} ${CONTAINER} cucumber $@

docker rm ${NAME}

