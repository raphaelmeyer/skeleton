#!/bin/bash

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PROJECT_ROOT=$( cd "${SCRIPT_DIR}/.." && pwd )

source ${PROJECT_ROOT}/toolchain.conf

SRC_HOST=${PROJECT_ROOT}/source
SRC_GUEST=/home/user/src

VOLUMES="--volumes-from avr-workspace -v ${SRC_HOST}:${SRC_GUEST}:ro"
CONTAINER="${AVR_IMG}:${AVR_VER}"

