########################################################################

BASE = 1.0.1

########################################################################

all: module device

module: module-exe module-features module-tests
device: device-exe device-features device-tests

ci: ci-module ci-device ci-reports

########################################################################

module-exe:            #/ build internet module executable
module-tests:          #/ run module tests
module-features:       #/ check module features
module-wip:            #/ check module work in progress
module-deploy:         #/ install application on internet module

device-exe:            #/ build doorbell device firmware
device-tests:          #/ run device tests
device-features:       #/ check device features
device-wip:            #/ check device work in progress
device-deploy:         #/ install doorbell firmware on device

module-tests-target:   #/ run module tests on target hardware

########################################################################

module-exe: src-ybpi artifacts
	./cmake-ybpi --build . --target $@
	docker cp ybpi-workspace:/workspace/module/module-exe/$@ artifacts/

module-features: module-cucumber
	./module-features.sh -f pretty --tag ~@wip

module-wip: module-cucumber
	./module-features.sh -f pretty --tag @wip --wip

module-tests: application-test
	./run-amd64 module/application-test/application-test

module-deploy: module-exe
	-ssh root@rpi2 killall -9 module-exe
	scp artifacts/module-exe root@rpi2:
	ssh root@rpi2 ./module-exe &

application-test: src-amd64
	./cmake-amd64 --build . --target $@

########################################################################

module-tests-target: application-test-target driver-test-target
	scp artifacts/application-test-target root@rpi2:
	scp artifacts/driver-test-target root@rpi2:
	ssh root@rpi2 ./application-test-target
	ssh root@rpi2 ./driver-test-target

application-test-target: src-ybpi artifacts
	./cmake-ybpi --build . --target application-test
	docker cp ybpi-workspace:/workspace/module/application-test/application-test artifacts/$@

driver-test-target: src-ybpi artifacts
	./cmake-ybpi --build . --target driver-test
	docker cp ybpi-workspace:/workspace/module/driver-test/driver-test artifacts/$@

########################################################################

device-exe: src-avr artifacts
	./cmake-avr --build . --target $@
	docker cp avr-workspace:/workspace/device/device-exe/$@ artifacts/
	docker cp avr-workspace:/workspace/device/device-exe/$@.hex artifacts/

device-features: device-cucumber
	./device-features.sh -f pretty --tag ~@wip

device-wip: device-cucumber
	./device-features.sh -f pretty --tag @wip --wip

device-tests: device-test
	./run-amd64 device/device-test/device-test

device-test: src-amd64
	./cmake-amd64 --build . --target $@

device-deploy: device-exe
	./avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:device/device-exe/device-exe.hex

########################################################################

module-cucumber: src-amd64
	./cmake-amd64 --build . --target module-cucumber

device-cucumber: src-amd64
	./cmake-amd64 --build . --target device-cucumber

########################################################################

ci-module: module-exe ci-module-features ci-module-tests

ci-device: device-exe ci-device-features ci-device-tests

ci-module-features: module-cucumber
	./run-amd64 mkdir -p reports/features
	./module-features.sh -t ~@wip -f progress -f html -o /workspace/reports/features/module.html -f json -o /workspace/reports/features/module.json

ci-module-tests: application-test
	./run-amd64 mkdir -p reports/tests
	./run-amd64 module/application-test/application-test --gtest_output=xml:reports/tests/

ci-device-features: device-cucumber
	./run-amd64 mkdir -p reports/features
	./device-features.sh -t ~@wip -f progress -f html -o /workspace/reports/features/device.html -f json -o /workspace/reports/features/device.json

ci-device-tests: device-test
	./run-amd64 mkdir -p reports/tests
	./run-amd64 device/device-test/device-test --gtest_output=xml:reports/tests/

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
	./cmake-amd64 --build . --target clean

clean-ybpi: src-ybpi
	./cmake-ybpi --build . --target clean

clean-avr: src-avr
	./cmake-avr --build . --target clean

########################################################################

src-amd64: tools/.amd64-workspace
	./cmake-amd64 /home/user/src

src-ybpi: tools/.ybpi-workspace source/arm-poky-linux-gnueabi.cmake
	./cmake-ybpi -DCMAKE_TOOLCHAIN_FILE=/home/user/src/arm-poky-linux-gnueabi.cmake /home/user/src

src-avr: tools/.avr-workspace source/gcc-avr.cmake
	./cmake-avr -DCMAKE_TOOLCHAIN_FILE=/home/user/src/gcc-avr.cmake /home/user/src

########################################################################

tools/.ybpi-workspace:
	-docker rm -v ybpi-workspace
	docker create --name ybpi-workspace raphaelmeyer/base:$(BASE)
	touch $@

tools/.amd64-workspace:
	-docker rm -v amd64-workspace
	docker create --name amd64-workspace raphaelmeyer/base:$(BASE)
	touch $@

tools/.avr-workspace:
	-docker rm -v avr-workspace
	docker create --name avr-workspace raphaelmeyer/base:${BASE}
	touch $@

########################################################################

help:
	@echo
	@grep -E "^(\S+)\s*:\s*#/\s*(.*)$$" $(lastword $(MAKEFILE_LIST))
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
	./cmake-amd64 --build . --target test


