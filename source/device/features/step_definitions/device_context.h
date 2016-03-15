#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>
#include <device/gpio.h>
#include <device/timer.h>

#include <avr/io.h>

#include "pwm_spy.h"

class DeviceContext
{
public:
  DeviceContext()
    : _button_register(&PIND)
    , _button_pin(6)
    , _gpio()
    , _bell()
    , _timer()
    , _device()
  {
  }

  void start()
  {
    // Most of the following is duplicate code from "main".
    // Is there something we can do about it?
    Gpio_init(&_gpio, Port_D, Pin_6);
    Timer_init(&_timer);

    Device_init(&_device, (IPwm *)&_bell.impl(), &_gpio, &_timer);
  }

  void advance(uint32_t millisecond_ticks) {
    for(uint32_t tick = 0; tick < millisecond_ticks; ++tick) {
      Timer_update(&_timer);
      Device_loop(&_device);
    }
  }

  void press_button() {
    // TODO bounce/chatter
    *_button_register |= (1 << _button_pin);
    advance(1);
    *_button_register &= ~(1 << _button_pin);
    advance(1);
  }

  Spy::Pwm & bell() { return _bell; }

private:
  uint8_t volatile * _button_register;
  uint8_t const _button_pin;

  Gpio _gpio;
  Spy::Pwm _bell;
  Timer _timer;
  Device _device;
};

#endif //SKELETON_DEVICE_CONTEXT_H
