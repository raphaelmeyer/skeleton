#include "application/gpio.h"

namespace Module {
namespace Gpio {

std::string const Path::Base = "/sys/class/gpio";
std::string const Path::Enable = Base + "/export";

static std::string const Dummy = "";


Path::Path(uint32_t number)
  : _number(number)
  , _direction(Base + "/gpio" + std::to_string(number) + "/direction")
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

std::string const & Path::edge() const
{
  return Dummy;
}

std::string const & Path::value() const
{
  return Dummy;
}

}
}
