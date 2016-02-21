########################################################################

BASE = 1.0.1

########################################################################

all: controller device

controller: controller-exe controller-features controller-tests
device: device-exe device-features device-tests

ci: ci-controller ci-device ci-reports

########################################################################

controller-exe:
controller-tests:
controller-features:
controller-wip:

device-exe:
device-tests:
device-features:
device-wip:

########################################################################

controller-exe: src-target artifacts
	./cmake-target --build . --target $@
	docker cp target-workspace:/workspace/controller/controller-exe/$@ artifacts/

controller-features: controller-cucumber
	./controller-features.sh -f pretty --tag ~@wip

controller-wip: controller-cucumber
	./controller-features.sh -f pretty --tag wip --@wip

controller-tests: application-test
	./run-amd64 controller/application-test/application-test

application-test: src-amd64
	./cmake-amd64 --build . --target $@

########################################################################

device-exe: src-avr artifacts
	./cmake-avr --build . --target $@
	docker cp avr-workspace:/workspace/device/device-exe/$@ artifacts/
	docker cp avr-workspace:/workspace/device/device-exe/$@.hex artifacts/

device-features: device-cucumber

device-wip: device-cucumber

device-tests: device-test
	./run-amd64 device/device-test/device-test

device-test: src-amd64
	./cmake-amd64 --build . --target $@

########################################################################

controller-cucumber: src-amd64
	./cmake-amd64 --build . --target controller-cucumber

device-cucumber: src-amd64
	./cmake-amd64 --build . --target device-cucumber

########################################################################

ci-controller: controller-exe ci-controller-features ci-controller-tests

ci-device: device-exe ci-device-features ci-device-tests

ci-controller-features: controller-cucumber
	./run-amd64 mkdir -p reports/features
	./controller-features.sh -t ~@wip -f progress -f html -o /workspace/reports/features/controller.html -f json -o /workspace/reports/features/controller.json

ci-controller-tests: application-test
	./run-amd64 mkdir -p reports/tests
	./run-amd64 controller/application-test/application-test --gtest_output=xml:reports/tests/

ci-device-features:
	./run-amd64 mkdir -p reports/features

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

clean: clean-amd64 clean-target clean-avr clean-artifacts

ci-clean: clean-workspace clean-artifacts

clean-workspace:
	-docker rm -v amd64-workspace
	-docker rm -v target-workspace
	-docker rm -v avr-workspace
	rm -f tools/.amd64-workspace
	rm -f tools/.target-workspace
	rm -f tools/.avr-workspace

clean-artifacts:
	rm -rf artifacts
	rm -rf reports

clean-amd64: src-amd64
	./cmake-amd64 --build . --target clean

clean-target: src-target
	./cmake-target --build . --target clean

clean-avr: src-avr
	./cmake-avr --build . --target clean

########################################################################

src-amd64: tools/.amd64-workspace
	./cmake-amd64 /home/user/src

src-target: tools/.target-workspace source/arm-poky-linux-gnueabi.cmake
	./cmake-target -DCMAKE_TOOLCHAIN_FILE=/home/user/src/arm-poky-linux-gnueabi.cmake /home/user/src

src-avr: tools/.avr-workspace source/gcc-avr.cmake
	./cmake-avr -DCMAKE_TOOLCHAIN_FILE=/home/user/src/gcc-avr.cmake /home/user/src

########################################################################

tools/.target-workspace:
	-docker rm -v target-workspace
	docker create --name target-workspace raphaelmeyer/base:$(BASE)
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

# TODO
# device-install:
# 	»·./avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:fw.hex

# Run tests registered with cmake.
# Does not (re)build anything.
#cmake-test-host: src-amd64/
#	./cmake-amd64 --build . --target test
