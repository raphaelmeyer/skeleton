#include "application/gpio.h"

namespace Module {
namespace Gpio {

std::string const Path::Enable = "/sys/class/gpio/export";

Path::Path(uint32_t number)
  : _number(number)
{
}

std::string const & Path::enable() {
  return Enable;
}

uint32_t Path::number() const {
  return _number;
}

}
}
