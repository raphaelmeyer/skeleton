#!/bin/bash

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PROJECT_ROOT=$( cd "${SCRIPT_DIR}/.." && pwd )

source ${SCRIPT_DIR}/env-amd64.sh
source ${PROJECT_ROOT}/hardware.conf

cd ${PROJECT_ROOT}

RPI_IP=`getent hosts ${RPI_HOST} | awk '{ print $1 }'`

docker run --rm -t --add-host ${RPI_HOST}:${RPI_IP} -e RPI_HOST=${RPI_HOST} -w ${SRC_GUEST}/module/acceptance-test-target ${VOLUMES} ${CONTAINER} cucumber $@

