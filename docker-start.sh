#!/bin/sh

# Creator:    VPR
# Created:    March 11th, 2022
# Updated:    March 11th, 2022

DOCKER_IMAGE="omega-zero-dev"

docker run -itv ${PWD}:/home/oz/omega-zero "${DOCKER_IMAGE}"
