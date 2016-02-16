#include "application/application.h"

#include <iostream>
#include <fstream>
#include <thread>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <poll.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

namespace WS {

  Application::Application() {
  }

  void Application::run() {

    std::thread task(&Application::int_example, this);

    i2c_example();

    task.join();
  }

  void Application::i2c_example()
  {
    std::cout << "open device\n";

    this->_fd = open("/dev/i2c-1", O_RDWR);
    if(this->_fd < 0) {
      abort("cannot open device");
    }

    std::cout << "set slave address\n";

    int const address = 0x31;
    if(ioctl(this->_fd, I2C_SLAVE, address) < 0) {
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

  void Application::int_example()
  {
    std::ofstream activate("/sys/class/gpio/export");
    activate << "17";
    activate.close();

    std::ofstream direction("/sys/class/gpio/gpio17/direction");
    direction << "out";
    direction.close();

    std::ofstream edge("/sys/class/gpio/gpio17/edge");
    edge << "rising";
    edge.close();

    int fd = open("/sys/class/gpio/gpio17/value", O_RDONLY);
    if (fd < 0) {
      abort("failed to open gpio17");
    }

    pollfd pfd;
    uint8_t buf[8];

    pfd.fd = fd;
    pfd.events = POLLPRI;

    lseek(fd, 0, SEEK_SET);
    read(fd, buf, sizeof(buf));

    int32_t const no_timeout = -1;

    uint32_t num = 5;
    while(--num) {
      int result = poll(&pfd, 1, no_timeout);
      if(result > 0) {
        std::cout << "interrupt " << num << "\n";
      }
      lseek(fd, 0, SEEK_SET);
      read(fd, buf, sizeof(buf));
    }
  }

  void Application::abort(std::string const & message) {
    std::cout << message << "\n";
    throw;
  }

}

