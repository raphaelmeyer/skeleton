########################################################################

YBPI = 2.0.0
BASE = 1.0.1

########################################################################

all: app-target acceptance test fw

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

########################################################################

unit-test-host: app-test-host

acceptance-test-host: src-host
	./cmake-amd64 --build . --target $@

app-test-host: src-host
	./cmake-amd64 --build . --target app-test

app-target: src-target artifacts
	./cmake-target --build . --target skeleton
	docker cp target-workspace:/workspace/skeleton artifacts/

# Run tests registered with cmake.
# Does not (re)build anything.
cmake-test-host: src-host/
	./cmake-amd64 --build . --target test

########################################################################

clean: clean-host clean-target
	rm -rf artifacts

clean-host: src-host
	./cmake-amd64 --build . --target clean

clean-target: src-target
	./cmake-target --build . --target clean

########################################################################

src-host: tools/.amd64-workspace
	./cmake-amd64 /home/user/src

src-target: tools/.target-workspace source/arm-poky-linux-gnueabi.cmake
	./cmake-target -DCMAKE_TOOLCHAIN_FILE=/home/user/src/arm-poky-linux-gnueabi.cmake /home/user/src

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

########################################################################

clean-workspace:
	-docker rm -v amd64-workspace
	-docker rm -v target-workspace
	-docker rm -v avr-workspace
	rm -f tools/.host-workspace
	rm -f tools/.target-workspace
	rm -f tools/.avr-workspace


########################################################################
# TODO
########################################################################

fw: fw-main

fw-main: src-avr artifacts
	./cmake-avr --build . --target $@
	docker cp avr-workspace:/workspace/$@/$@.elf artifacts/
	docker cp avr-workspace:/workspace/$@/$@.hex artifacts/

src-avr: tools/.avr-workspace source/gcc-avr.cmake
	./cmake-avr -DCMAKE_TOOLCHAIN_FILE=/home/user/src/gcc-avr.cmake /home/user/src

clean-fw:
	./cmake-avr --build . --target clean

install: fw
	»·./avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:fw.hex

