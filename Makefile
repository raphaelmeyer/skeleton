########################################################################

BASE = 1.0.1

########################################################################

all: controller device

controller: controller-exe controller-test
device: device-exe device-test

########################################################################

controller-exe:
controller-test: controller-features application-test
controller-features:
controller-wip:

device-exe:
device-test:

########################################################################

controller-exe: src-target artifacts
	./cmake-target --build . --target $@
	docker cp target-workspace:/workspace/controller/controller-exe/$@ artifacts/


application-test: src-amd64
	./cmake-amd64 --build . --target $@
	./run-amd64 controller/application-test/$@


controller-features: controller-cucumber
	./controller-features.sh -f pretty --tag ~@wip

controller-wip: controller-cucumber
	./controller-features.sh -f pretty --tag wip --@wip

controller-cucumber: src-amd64
	./cmake-amd64 --build . --target controller-cucumber

device-exe: src-avr
	./cmake-avr --build . --target $@
	docker cp avr-workspace:/workspace/device/device-exe/$@ artifacts/
	docker cp avr-workspace:/workspace/device/device-exe/$@.hex artifacts/

device-test: src-amd64
	./cmake-amd64 --build . --target $@
	./run-amd64 device/device-test/$@

########################################################################

#all: app-target acceptance test fw

ci: app-target acceptance-test-host unit-test-host fw-main
	./run-amd64 rm -rf results
	./run-amd64 mkdir -p results/features
	./run-amd64 app-test/app-test --gtest_output=xml:results/unit-test/
	./acceptance-test-host.sh -t ~@wip -f progress -f html -o /workspace/results/features/acceptance-test.html -f junit -o /workspace/results/acceptance-test -f json -o /workspace/results/acceptance-test.json
	rm -rf artifacts/results
	docker cp amd64-workspace:/workspace/results/ artifacts/

acceptance: acceptance-test-host
	./acceptance-test-host.sh -f pretty --tag ~@wip

wip: acceptance-test-host
	./acceptance-test-host.sh -f pretty --tag wip --@wip

test: unit-test-host
	./run-amd64 app-test/app-test

clean: clean-amd64 clean-target clean-avr clean-artifacts

########################################################################

unit-test-host: app-test-host

acceptance-test-host: src-amd64
	./cmake-amd64 --build . --target $@

app-test-host: src-amd64
	./cmake-amd64 --build . --target app-test

app-target: src-target artifacts
	./cmake-target --build . --target skeleton
	docker cp target-workspace:/workspace/main/skeleton artifacts/

# Run tests registered with cmake.
# Does not (re)build anything.
cmake-test-host: src-amd64/
	./cmake-amd64 --build . --target test

########################################################################

clean-artifacts:
	rm -rf artifacts

clean-amd64: src-amd64
	./cmake-amd64 --build . --target clean

clean-target: src-target
	./cmake-target --build . --target clean

clean-avr: src-avr
	./cmake-avr --build . --target clean

clean-workspace:
	-docker rm -v amd64-workspace
	-docker rm -v target-workspace
	-docker rm -v avr-workspace
	rm -f tools/.amd64-workspace
	rm -f tools/.target-workspace
	rm -f tools/.avr-workspace

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

artifacts:
	mkdir -p artifacts


# TODO
# device-install:
# 	»·./avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:fw.hex

