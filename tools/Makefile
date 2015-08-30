
HOST=0.1.0

########################################################################

host-sdk: host-sdk/.done

########################################################################

host-sdk/.done: host-sdk/Dockerfile
	-docker rmi host-sdk:${HOST}
	docker build -t host-sdk:${HOST} host-sdk
	touch $@

