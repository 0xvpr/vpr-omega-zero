#!/bin/bash

# Created by:   VPR
# Created:      March 11th, 2022

# Updated by:   VPR
# Updated:      March 15th, 2025

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

ROOT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

DOCKER_FILE="Dockerfile"
DOCKER_IMAGE="omega-zero-dev"
USER_MOD="$(id -u):$(id -g)"

# Builds docker image using root Dockerfile and runs cmake for installation
[[ $(docker image ls -a | grep omega-zero-dev) ]] || docker build -f "${DOCKER_FILE}" -t "${DOCKER_IMAGE}" .
docker run -u ${USER_MOD} -itv ${ROOT_DIR}:/opt/omega-zero "${DOCKER_IMAGE}" /bin/bash -c "cmake -B docker-build && cmake --build docker-build"
