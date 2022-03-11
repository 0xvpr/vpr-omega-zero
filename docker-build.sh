#!/bin/sh

# Creator:    VPR
# Created:    March 11th, 2022
# Updated:    March 11th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

DOCKER_FILE="Dockerfile"
DOCKER_IMAGE="omega-zero-dev"

# Builds docker image using root Dockerfile
docker build -f "${__docker_file}" -t "${DOCKER_IMAGE}" .
