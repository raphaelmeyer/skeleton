# Walking skeleton

[![Build Status](https://travis-ci.org/raphaelmeyer/skeleton.svg?branch=master)](https://travis-ci.org/raphaelmeyer/skeleton/)

## Hardware


                arduino       ada 757       rpi
                ---------     --------      -------
    bell    :   6   (PD6)
    button  :   7   (PD7)

    vcc     :   5V        --- HV    LV ---  1 (3.3)
    signal  :   8   (PB0) --- B1    A1 ---  11 (17)

    gnd     :   GND       --- GND  GND ---  9 (GND)

                                            18 (24)
                                            29  (5)
                                            37 (26)


![schematic](doc/schematic.jpg?raw=true "schematic")


## Setup

Install the [image](https://www.dropbox.com/s/tum9hzxbb5pnc2c/ybpi-rpi2-image-raspberrypi2_2.3.0.rpi-sdimg?raw=1) to a SD card and resize the root partition:

    $ sudo dd if=ybpi-rpi2-image-raspberrypi2_2.3.0.rpi-sdimg of=/dev/sdX
    $ sudo parted /dev/sdX resizepart 2 1024M
    $ sudo resize2fs /dev/sdX2


Configure and reboot the target hardware:

    make module-configure


Get an overview of the most important make targets:

    make help


## Install and run

    make device-deploy
    make module-deploy


## Run hardware tests

In order to run the unit tests on the Raspberry Pi target hardware,
connect a loopback cable from GPIO 5 (pin 29) to GPIO 26 (pin 37):

    make module-tests-target


To run the feature tests on the Raspberry Pi target hardware,
connect a loopback cable from GPIO 17 (pin 11) to GPIO 24 (pin 18):

    make module-features-target


