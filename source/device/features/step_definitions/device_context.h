#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>
#include <device/gpio.h>
#include <device/timer.h>

#include "button_fake.h"
#include "pwm_spy.h"

#include <thread>
#include <chrono>

class DeviceContext
{
public:
  DeviceContext()
    : _gpio()
    , _bell()
    , _timer()
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
      Timer_init(&_timer);

      Device_init(&_device, (IPwm *)&_bell.impl(), &_gpio, &_timer);
      while(_running) {
        Device_loop(&_device);
      }
    });
  }

  void advance(uint32_t millisecond_ticks) {
    for(uint32_t tick = 0; tick < millisecond_ticks; ++tick) {
      using namespace std::chrono_literals;
      Timer_update(&_timer);
      std::this_thread::sleep_for(1ms);
    }
  }

  void stop()
  {
    _running = false;
    _device_thread.join();
  }

  Spy::Pwm & bell() { return _bell; }
  Fake::Button & button() { return _button; }
  Timer & timer() { return _timer; }

private:
  Gpio _gpio;
  Spy::Pwm _bell;
  Timer _timer;
  Device _device;

  Fake::Button _button;

  bool _running;
  std::thread _device_thread;
};

#endif //SKELETON_DEVICE_CONTEXT_H
