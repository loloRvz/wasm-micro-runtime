FROM ubuntu:20.04 as tools

ENV DEBIAN_FRONTEND="noninteractive"
RUN apt-get update && apt-get install -y git cmake \
	build-essential jq \
	python3 python3-pip \
	curl
RUN pip3 install kconfiglib

RUN curl -Lo- https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz | tar -C /opt -xz \
    && mv /opt/wasi-sdk-12.0 /opt/wasi-sdk
ENV PATH=$PATH:/opt/wasi-sdk/bin

WORKDIR /src
COPY . .
WORKDIR /src/samples/wafle
RUN ./build.sh
