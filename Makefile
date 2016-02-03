########################################################################

YBPI = 2.0.0

########################################################################

all: app-target acceptance test

ci: app-target acceptance-test-host unit-test-host
	./run-host rm -rf results
	./run-host mkdir -p results/features
	./run-host app-test/app-test --gtest_output=xml:results/unit-test/
	./acceptance-test-host.sh -t ~@wip -f progress -f html -o /workspace/results/features/acceptance-test.html -f junit -o /workspace/results/acceptance-test -f json -o /workspace/results/acceptance-test.json
	rm -rf artifacts/results
	docker cp host-workspace:/workspace/results/ artifacts/

acceptance: acceptance-test-host
	./acceptance-test-host.sh -f pretty --tag ~@wip

wip: acceptance-test-host
	./acceptance-test-host.sh -f pretty --tag wip --@wip

test: unit-test-host
	./run-host app-test/app-test

########################################################################

unit-test-host: app-test-host

acceptance-test-host: src-host
	./cmake-host --build . --target $@

app-test-host: src-host
	./cmake-host --build . --target app-test

app-target: src-target artifacts
	./cmake-target --build . --target skeleton
	docker cp target-workspace:/workspace/skeleton artifacts/

# Run tests registered with cmake.
# Does not (re)build anything.
cmake-test-host: src-host/
	./cmake-host --build . --target test

########################################################################

clean: clean-host clean-target
	rm -rf artifacts

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

tools/.target-workspace:
	-docker rm -v target-workspace
	docker create --name target-workspace raphaelmeyer/ybpi-base:$(YBPI)
	touch $@

tools/.host-workspace:
	-docker rm -v host-workspace
	docker create --name host-workspace raphaelmeyer/ybpi-base:$(YBPI)
	touch $@

########################################################################

artifacts:
	mkdir -p artifacts

########################################################################

clean-workspace:
	-docker rm -v host-workspace
	-docker rm -v target-workspace
	rm tools/.host-workspace
	rm tools/.target-workspace


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

tools/.avr-workspace:
	-docker rm -v avr-workspace
	docker create --name avr-workspace raphaelmeyer/avr-sdk
	touch $@

clean-fw:
	./cmake-avr --build . --target clean

avr-clean:
	-docker rm -v avr-workspace
	rm -rf tools/.avr-workspace

install: fw
	»·./avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:fw.hex

