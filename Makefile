
all: check app-target

check: check-host

check-host: tests-host
	echo "Run accpetance test on host"
	echo "Run unit test on host"

tests-host:

app-target:
	echo "build application for target"

########################################################################

target-shell: tools/.target-workspace
	docker run --rm -it --volumes-from target-workspace ybpi-sdk /bin/bash

host-shell: tools/.host-workspace tools/host-gcc/.done
	docker run --rm -it --volumes-from host-workspace host-gcc /bin/bash

########################################################################

tools/.target-workspace:
	-docker rm -v target-workspace
	docker create --name target-workspace ybpi-sdk-data
	touch $@

tools/.host-workspace: tools/host-gcc-data/.done
	-docker rm -v host-workspace
	docker create --name host-workspace host-gcc-data
	touch $@

########################################################################

toolchain: tools/host-gcc/.done tools/host-gcc-data/.done

tools/host-gcc/.done: tools/host-gcc/Dockerfile
	-docker rmi host-gcc
	docker build -t host-gcc tools/host-gcc
	touch $@

tools/host-gcc-data/.done: tools/host-gcc-data/Dockerfile
	-docker rm -v host-workspace
	rm tools/.host-workspace
	-docker rmi host-gcc-data
	docker build -t host-gcc-data tools/host-gcc-data
	touch $@

########################################################################

clean-workspace:
	-docker rm -v host-workspace
	-docker rm -v target-workspace
	rm tools/.host-workspace
	rm tools/.target-workspace



