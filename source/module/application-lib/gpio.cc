#include "application/gpio.h"

namespace Module {
namespace Gpio {

Path::Path(uint32_t number)
  : _number(number)
{
}

uint32_t Path::number() const {
  return _number;
}

}
}
