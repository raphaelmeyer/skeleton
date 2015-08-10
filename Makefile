
all: check app-target

check: check-host

check-host: tests-host
	echo "Run accpetance test on host"
	echo "Run unit test on host"

tests-host:

app-target:
	echo "build application for target"

########################################################################

target-shell:
	docker run --rm -it --volumes-from target-workspace ybpi-sdk /bin/bash

host-shell:
	docker run --rm -it --volumes-from host-workspace host-gcc /bin/bash

########################################################################

.target-workspace:
	-docker rm -v target-workspace
	docker create --name target-workspace ybpi-sdk-data
	touch $@

.host-workspace: host-gcc-data/.done
	-docker rm -v host-workspace
	docker create --name host-workspace host-gcc-data
	touch $@

toolchain: host-gcc/.done host-gcc-data/.done

host-gcc/.done: host-gcc/Dockerfile
	-docker rmi host-gcc
	docker build -t host-gcc host-gcc
	touch $@

host-gcc-data/.done: host-gcc-data/Dockerfile
	-docker rmi host-gcc-data
	docker build -t host-gcc-data host-gcc-data
	touch $@

