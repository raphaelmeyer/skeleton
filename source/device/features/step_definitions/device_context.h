#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>
#include <device/gpio.h>

#include "button_fake.h"
#include "pwm_spy.h"

#include <thread>

class DeviceContext
{
public:
  DeviceContext()
    : _gpio()
    , _bell()
    , _device()
    , _button(&PINB, 0)
    , _device_thread()
  {
  }

  void start()
  {

    // _bell.init();

    _device_thread = std::thread([&]{
      Gpio_init(&_gpio, Port_B, Pin_0);

      Device_init(&_device, (IPwm *)&_bell.impl(), &_gpio);
      Device_start(&_device);
    });
  }

  void stop()
  {
    Device_stop(&_device);
    _device_thread.join();
  }

  Spy::Pwm & bell() { return _bell; }
  Fake::Button & button() { return _button; }

private:
  Gpio _gpio;
  Spy::Pwm _bell;
  Device _device;

  Fake::Button _button;

  std::thread _device_thread;
};

#endif //SKELETON_DEVICE_CONTEXT_H
