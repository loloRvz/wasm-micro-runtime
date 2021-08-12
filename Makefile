DOCKER_IMAGE ?= wamr-test
DOCKER_TAG ?= latest

all: build
.PHONY: all

build: Dockerfile
	tar -c --exclude-vcs . | \
		docker build -f $^ -t $(DOCKER_IMAGE):$(DOCKER_TAG) -
.PHONY: build

shell:
	docker run --rm -it $(DOCKER_IMAGE):$(DOCKER_TAG)
.PHONY: shell
