#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>
#include <device/gpio.h>

#include "gpio_stub.h"
#include "pwm_spy.h"

#include <thread>

class DeviceContext
{
public:
  DeviceContext()
    : _button()
    , _bell()
    , _gpio()
    , _device()
    , _device_thread()
  {
  }

  void start()
  {
    _device_thread = std::thread([&]{
      // TODO duplication -> extract to method
      Device_init(&_device, (IPwm *)&_bell.impl(), (IGpio *)&_gpio);
      Device_start(&_device);
    });
  }

  void stop()
  {
    Device_stop(&_device);
    _device_thread.join();
  }

  PwmSpy & bell() { return _bell; }
  ButtonStub & button() { return _button; }

private:
  ButtonStub _button;
  PwmSpy _bell;

  Gpio _gpio;
  Device _device;

  std::thread _device_thread;
};

#endif //SKELETON_DEVICE_CONTEXT_H
