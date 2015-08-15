
host-toolchain: host-gcc/.done host-gcc-data/.done

########################################################################

host-gcc/.done: host-gcc/Dockerfile
	-docker rmi host-gcc
	docker build -t host-gcc host-gcc
	touch $@

host-gcc-data/.done: host-gcc-data/Dockerfile
	-docker rm -v host-workspace
	rm .host-workspace
	-docker rmi host-gcc-data
	docker build -t host-gcc-data host-gcc-data
	touch $@

