########################################################################

all: module device

module: module-exe module-features module-tests
device: device-exe device-features device-tests

ci: ci-module ci-device ci-reports

########################################################################

module-exe:               #/ build internet module executable
module-tests:             #/ run module tests
module-features:          #/ check module features
module-wip:               #/ check module work in progress
module-deploy:            #/ install application on internet module

device-exe:               #/ build doorbell device firmware
device-tests:             #/ run device tests
device-features:          #/ check device features
device-wip:               #/ check device work in progress
device-deploy:            #/ install doorbell firmware on device

module-tests-target:      #/ run module tests on target hardware
module-features-target:   #/ check module features on target hardware
module-configure:         #/ configure the target hardware

########################################################################

include toolchain.conf
include hardware.conf

########################################################################

module-exe: src-ybpi artifacts
	./scripts/cmake-ybpi --build . --target $@
	docker cp ybpi-workspace:/workspace/module/module-exe/$@ artifacts/

module-features: module-cucumber
	./scripts/module-features.sh -f pretty --tag ~@wip

module-wip: module-cucumber
	./scripts/module-features.sh -f pretty --tag @wip --wip

module-tests: application-test
	./scripts/run-amd64 module/application-test/application-test

module-deploy: module-exe
	-ssh root@$(RPI_HOST) killall -9 module-exe
	scp artifacts/module-exe root@$(RPI_HOST):
	ssh root@$(RPI_HOST) ./module-exe &

application-test: src-amd64
	./scripts/cmake-amd64 --build . --target $@

########################################################################

module-tests-target: application-test-target driver-test-target
	-ssh root@$(RPI_HOST) killall -9 driver-test-target
	-ssh root@$(RPI_HOST) killall -9 application-test-target
	scp artifacts/application-test-target root@$(RPI_HOST):
	scp artifacts/driver-test-target root@$(RPI_HOST):
	ssh root@$(RPI_HOST) ./application-test-target
	ssh root@$(RPI_HOST) ./driver-test-target

module-features-target: module-deploy
	./scripts/module-features-target.sh -f pretty --tag ~@wip

application-test-target: src-ybpi artifacts
	./scripts/cmake-ybpi --build . --target application-test
	docker cp ybpi-workspace:/workspace/module/application-test/application-test artifacts/$@

driver-test-target: src-ybpi artifacts
	./scripts/cmake-ybpi --build . --target driver-test
	docker cp ybpi-workspace:/workspace/module/driver-test/driver-test artifacts/$@

########################################################################

device-exe: src-avr artifacts
	./scripts/cmake-avr --build . --target $@
	docker cp avr-workspace:/workspace/device/device-exe/$@ artifacts/
	docker cp avr-workspace:/workspace/device/device-exe/$@.hex artifacts/

device-features: device-cucumber
	./scripts/device-features.sh -f pretty --tag ~@wip

device-wip: device-cucumber
	./scripts/device-features.sh -f pretty --tag @wip --wip

device-tests: device-test
	./scripts/run-amd64 device/device-test/device-test

device-test: src-amd64
	./scripts/cmake-amd64 --build . --target $@

device-deploy: device-exe
	./scripts/avrdude -c arduino -p atmega328p -P $(ARDUINO_PORT) -b 115200 -U flash:w:device/device-exe/device-exe.hex

########################################################################

module-cucumber: src-amd64
	./scripts/cmake-amd64 --build . --target $@

device-cucumber: src-amd64
	./scripts/cmake-amd64 --build . --target $@

########################################################################

ci-module: module-exe ci-module-features ci-module-tests

ci-device: device-exe ci-device-features ci-device-tests

ci-module-features: module-cucumber
	./scripts/run-amd64 mkdir -p reports/features
	./scripts/module-features.sh -t ~@wip -f progress -f html -o /workspace/reports/features/module.html -f json -o /workspace/reports/features/module.json

ci-module-tests: application-test
	./scripts/run-amd64 mkdir -p reports/tests
	./scripts/run-amd64 module/application-test/application-test --gtest_output=xml:reports/tests/

ci-device-features: device-cucumber
	./scripts/run-amd64 mkdir -p reports/features
	./scripts/device-features.sh -t ~@wip -f progress -f html -o /workspace/reports/features/device.html -f json -o /workspace/reports/features/device.json

ci-device-tests: device-test
	./scripts/run-amd64 mkdir -p reports/tests
	./scripts/run-amd64 device/device-test/device-test --gtest_output=xml:reports/tests/

ci-reports:
	rm -rf reports/
	docker cp amd64-workspace:/workspace/reports reports

########################################################################

artifacts:
	mkdir -p artifacts

########################################################################

clean: clean-amd64 clean-ybpi clean-avr clean-artifacts

ci-clean: clean-workspace clean-artifacts

clean-workspace:
	-docker rm -v amd64-workspace
	-docker rm -v ybpi-workspace
	-docker rm -v avr-workspace
	rm -f tools/.amd64-workspace
	rm -f tools/.ybpi-workspace
	rm -f tools/.avr-workspace

clean-artifacts:
	rm -rf artifacts
	rm -rf reports

clean-amd64: src-amd64
	./scripts/cmake-amd64 --build . --target clean

clean-ybpi: src-ybpi
	./scripts/cmake-ybpi --build . --target clean

clean-avr: src-avr
	./scripts/cmake-avr --build . --target clean

########################################################################

src-amd64: tools/.amd64-workspace
	./scripts/cmake-amd64 /home/user/src

src-ybpi: tools/.ybpi-workspace source/arm-poky-linux-gnueabi.cmake
	./scripts/cmake-ybpi -DCMAKE_TOOLCHAIN_FILE=/home/user/src/arm-poky-linux-gnueabi.cmake /home/user/src

src-avr: tools/.avr-workspace source/gcc-avr.cmake
	./scripts/cmake-avr -DCMAKE_TOOLCHAIN_FILE=/home/user/src/gcc-avr.cmake /home/user/src

########################################################################

tools/.ybpi-workspace:
	-docker rm -v ybpi-workspace
	docker create --name ybpi-workspace $(BASE_IMG):$(BASE_VER)
	touch $@

tools/.amd64-workspace:
	-docker rm -v amd64-workspace
	docker create --name amd64-workspace $(BASE_IMG):$(BASE_VER)
	touch $@

tools/.avr-workspace:
	-docker rm -v avr-workspace
	docker create --name avr-workspace $(BASE_IMG):$(BASE_VER)
	touch $@

########################################################################

module-configure: source/module/conf/index.html source/module/conf/lighttpd.conf
	scp source/module/conf/lighttpd.conf root@$(RPI_HOST):/etc/lighttpd.conf
	scp source/module/conf/index.html root@$(RPI_HOST):/home/root/index.html
	ssh root@$(RPI_HOST) /sbin/reboot

########################################################################

help:
	@echo
	@grep -E "^(\S+)\s*:\s*#/\s*(.*)$$" $(firstword $(MAKEFILE_LIST))
	@echo

########################################################################

.SUFFIXES:

.PHONY: clean
.PHONY: clean-amd64 clean-ybpi clean-avr
.PHONY: clean-artifacts clean-workspace
.PHONY: ci-clean

########################################################################

# Run tests registered with cmake.
# Does not (re)build anything.
cmake-run-tests: src-amd64
	./scripts/cmake-amd64 --build . --target test


