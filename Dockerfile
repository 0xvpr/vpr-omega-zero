# Creator:    VPR
# Created:    January 27th, 2022
# Updated:    March 14th, 2025

FROM ubuntu:22.04

# Set env to avoid user input interruption during installation
ENV TZ=Etc/UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install deps
RUN apt-get update -y
RUN apt-get install -y --no-install-recommends \
cmake \
build-essential \
gcc \
gcc-multilib \
g++-multilib \
mingw-w64 \
mingw-w64-common \
mingw-w64-i686-dev \
mingw-w64-x86-64-dev

# Create omega-zero user && working directory
ENV HOME=/home/root
WORKDIR /opt/omega-zero
