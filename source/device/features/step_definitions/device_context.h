#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>

#include "gpio_stub.h"
#include "pwm_spy.h"

#include <thread>

class DeviceContext
{
public:
  DeviceContext()
    : _button()
    , _bell()
    , _device()
    , _device_thread()
  {
  }

  void start()
  {
    _device_thread = std::thread([&]{
      Device_init(&_device, (IPwm *)&_bell.impl(), (IGpio *)&_button.impl());
      Device_start(&_device);
    });
  }

  void stop()
  {
    Device_stop(&_device);
    _device_thread.join();
  }

  GpioStub & button() { return _button; }
  PwmSpy & bell() { return _bell; }

private:
  GpioStub _button;
  PwmSpy _bell;

  Device _device;

  std::thread _device_thread;
};

#endif //SKELETON_DEVICE_CONTEXT_H
