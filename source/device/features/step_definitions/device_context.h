#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>
#include <device/gpio.h>

#include "button_fake.h"
#include "pwm_spy.h"
#include "timer_stub.h"

#include <thread>
#include <chrono>

class DeviceContext
{
public:
  DeviceContext()
    : _gpio()
    , _bell()
    , _device()
    , _button(&PIND, 6)
    , _running(false)
    , _device_thread()
  {
  }

  void start()
  {
    _running = true;
    _device_thread = std::thread([&]{
      // Most of the following is duplicate code from "main".
      // Is there something we can do about it?
      Gpio_init(&_gpio, Port_D, Pin_6);

      Device_init(&_device, (IPwm *)&_bell.impl(), &_gpio, (ITimer *)&_timer);
      while(_running) {
        Device_loop(&_device);
      }
    });
  }

  void run_for(std::chrono::milliseconds const & ms) {
    std::this_thread::sleep_for(ms);
  }

  void stop()
  {
    _running = false;
    _device_thread.join();
  }

  Spy::Pwm & bell() { return _bell; }
  Fake::Button & button() { return _button; }
  Stub::Timer & timer() { return _timer; }

private:
  Gpio _gpio;
  Spy::Pwm _bell;
  Device _device;
  Stub::Timer _timer;

  Fake::Button _button;

  bool _running;
  std::thread _device_thread;
};

#endif //SKELETON_DEVICE_CONTEXT_H
