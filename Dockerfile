FROM ubuntu:focal

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get -y install \
    gcc-arm* \ 
    g++-arm* \
    cmake \
    vim