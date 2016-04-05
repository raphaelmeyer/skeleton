#include "application/gpio.h"

namespace Module {
namespace Gpio {

std::string const Path::Base = "/sys/class/gpio";
std::string const Path::Enable = Base + "/export";

Path::Path(uint32_t number)
  : _number(number)
  , _gpio(Base + "/gpio" + std::to_string(_number))
  , _direction(_gpio + "/direction")
  , _edge(_gpio + "/edge")
  , _value(_gpio + "/value")
{
}

std::string const & Path::enable() {
  return Enable;
}

uint32_t Path::number() const {
  return _number;
}

std::string const & Path::direction() const {
  return _direction;
}

std::string const & Path::edge() const {
  return _edge;
}

std::string const & Path::value() const {
  return _value;
}

}
}
