#ifndef SKELETON_GPIO_STUB_H
#define SKELETON_GPIO_STUB_H

#include <device/gpio.h>

class GpioStub
{
public:
  void press()
  {

  }

  Gpio & impl() { return _impl; }

private:
  Gpio _impl;
};

#endif //SKELETON_GPIO_STUB_H
