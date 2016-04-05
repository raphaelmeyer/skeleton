#include "application/poll.h"

#include <fstream>

#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

namespace Module
{

Poll::Poll()
  : _poll_fd(-1)
{
}

void Poll::setup(Gpio::Path & gpio)
{
  std::ofstream activate(gpio.enable());
  activate << gpio.number();
  activate.close();

  std::ofstream direction(gpio.direction());
  direction << "in";
  direction.close();

  std::ofstream edge(gpio.edge());
  edge << "rising";
  edge.close();

  _poll_fd = open(gpio.value().c_str(), O_RDONLY);
}

bool Poll::poll()
{
  int32_t const no_timeout = -1;

  pollfd pfd;
  uint8_t buf[8];

  pfd.fd = _poll_fd;
  pfd.events = POLLPRI;

  ::lseek(_poll_fd, 0, SEEK_SET);
  ::read(_poll_fd, buf, sizeof(buf));

  int32_t const result = ::poll(&pfd, 1, no_timeout);

  bool const interrupted = result > 0;

  return interrupted;
}


}
