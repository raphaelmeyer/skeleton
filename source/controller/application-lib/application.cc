#include "application/application.h"

#include <iostream>

#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

namespace WS {

  Application::Application() {
  }

  void Application::run() {

    std::cout << "open device\n";

    _fd = open("/dev/i2c-1", O_RDWR);
    if(_fd < 0) {
      abort("cannot open device");
    }

    std::cout << "set slave address\n";

    int const address = 0x31;
    if(ioctl(_fd, I2C_SLAVE, address) < 0) {
      abort("failed to set slave address");
    }

    get_register(address, 0x01);
    get_register(address, 0x2A);

  }

  void Application::get_register(int const address, uint8_t reg)
  {
    i2c_rdwr_ioctl_data command;
    i2c_msg messages[2];

    messages[0].addr = address;
    messages[0].flags = 0;
    messages[0].len = 1;
    messages[0].buf = &reg;

    uint8_t input[2];

    messages[1].addr = address;
    messages[1].flags = I2C_M_NOSTART | I2C_M_RD;
    messages[1].len = 2;
    messages[1].buf = input;

    command.msgs = messages;
    command.nmsgs = 2;
    if(ioctl(this->_fd, I2C_RDWR, &command) < 0) {
      abort("failed to read from slave");
    }

    std::cout << "read "
    << static_cast<uint32_t>(input[0])
    << " "
    << static_cast<uint32_t>(input[1])
    << "\n";
  }

  void Application::abort(std::string const & message) {
    std::cout << message << "\n";
    throw;
  }

}

