#include "application/application.h"

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

namespace WS {

  Application::Application() {
  }

  void Application::run() {
    std::cout << "Start ...\n";

    _fd = open("/dev/spidev0.0", O_RDWR);
    if(_fd < 0) {
      abort("cannot open device");
    }

    std::uint32_t mode = 0;
    int ret = ioctl(_fd, SPI_IOC_WR_MODE32, &mode);
    if(ret < 0) {
      abort("cannot set spi mode");
    }

    std::uint32_t speed = 0;
    ret = ioctl(_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if(ret < 0) {
      abort("cannot read spi speed");
    }
    std::cout << "  SPI speed = " << speed << "\n";

    std::cout << "Run ...\n";
    std::cout << "Shutdown ...\n";
    std::cout << "Done.\n";
  }

  void Application::abort(std::string const & message) {
    std::cout << message << "\n";
    throw;
  }

}

