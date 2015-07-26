
all: xyz

xyz:
	echo "build xyz"

shell: shell.sh
	shell.sh

build: build.sh
	build.sh

.PHONY: shell build

########################################################################

toolchain: host-gcc/.done host-gcc-data/.done

host-gcc/.done: host-gcc/Dockerfile
	docker build -t host-gcc host-gcc
	touch $@

host-gcc-data/.done: host-gcc-data/Dockerfile
	docker build -t host-gcc-data host-gcc-data
	touch $@

# docker create --name host-workspace host-gcc-data
# docker create --name target-workspace ybpi-sdk-data

# docker run --rm -it --volumes-from host-workspace host-gcc /bin/bash
# docker run --rm -it --volumes-from target-workspace ybpi-sdk /bin/bash

