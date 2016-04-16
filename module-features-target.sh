#!/bin/bash

PROJECT_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source ${PROJECT_ROOT}/env-amd64.sh

RPI=rpi2
RPI_IP=`getent hosts ${RPI} | awk '{ print $1 }'`

docker run --rm -t --add-host ${RPI}:${RPI_IP} -w ${SRC_GUEST}/module/acceptance-test-target ${VOLUMES} ${CONTAINER} cucumber $@

