all: check app-target

check: check-host

check-host: unit-test-host acceptance-test-host

unit-test-host: src-host
	./cmake-host --build . --target check

acceptance-test-host: src-host
	./cmake-host --build . --target $@
	./$(@).sh

app-test-host: src-host
	./cmake-host --build . --target app-test

app-target: src-target
	./cmake-target --build . --target skeleton

########################################################################

clean: clean-host clean-target

clean-host: src-host
	./cmake-host --build . --target clean

clean-target: src-target
	./cmake-target --build . --target clean

########################################################################

src-host: tools/.host-workspace
	./cmake-host /home/user/src

src-target: tools/.target-workspace source/arm-poky-linux-gnueabi.cmake
	./cmake-target -DCMAKE_TOOLCHAIN_FILE=/home/user/src/arm-poky-linux-gnueabi.cmake /home/user/src

########################################################################

HOST = 0.1.0
YBPI = 2.0.0

########################################################################

tools/.target-workspace:
	-docker rm -v target-workspace
	docker create --name target-workspace ybpi-sdk-data:$(YBPI)
	touch $@

tools/.host-workspace:
	-docker rm -v host-workspace
	docker create --name host-workspace host-gcc-data:$(HOST)
	touch $@

########################################################################

clean-workspace:
	-docker rm -v host-workspace
	-docker rm -v target-workspace
	rm tools/.host-workspace
	rm tools/.target-workspace

