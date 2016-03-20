#ifndef SKELETON_BUTTON_STUB_H
#define SKELETON_BUTTON_STUB_H

#include <device/gpio.h>

namespace Stub
{

class Gpio
{
public:
  Gpio(uint8_t volatile * port, uint8_t pin)
    : _gpio()
    , _port(port)
    , _pin(pin)
  {
  }

  void set() {
    *_port |= (1 << _pin);
  }

  void clear() {
    *_port &= ~(1 << _pin);
  }

  ::Gpio & impl() { return _gpio; }

private:
  ::Gpio _gpio;

  uint8_t volatile * _port;
  uint8_t const _pin;
};

} // namespace

#endif //SKELETON_BUTTON_STUB_H
