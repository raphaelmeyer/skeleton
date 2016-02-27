#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include "gpio_stub.h"
#include "pwm_spy.h"

class DeviceContext
{
public:
  DeviceContext()
    : _button()
    , _bell()
  {
  }

  void start()
  {

  }

  void stop()
  {

  }

  GpioStub & button() { return _button; }
  PwmSpy & bell() { return _bell; }

private:
  GpioStub _button;
  PwmSpy _bell;
};

#endif //SKELETON_DEVICE_CONTEXT_H
