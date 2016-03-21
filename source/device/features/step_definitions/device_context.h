#ifndef SKELETON_DEVICE_CONTEXT_H
#define SKELETON_DEVICE_CONTEXT_H

#include <device/device.h>
#include <device/system_tick.h>
#include <device/timer.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "pwm_spy.h"
#include "gpio_stub.h"

class DeviceContext
{
public:
  DeviceContext()
    : _button_stub(&PIND, 7)
    , _notify_stub(&PORTB, 0)
    , _bell_spy()
    , _now(0)
    , _button(_button_stub.impl())
    , _notify(_notify_stub.impl())
    , _bell((IPwm &)_bell_spy.impl())
    , _timer()
    , _device()
  {
  }

  void start()
  {
    // Most of the following is duplicate code from "main".
    // Is there something we can do about it?

    SystemTick_init();

    Gpio_init(&_button, Port_D, Pin_7);
    Timer_init(&_timer);

    Device_init(&_device, &_bell, &_button, &_timer);
  }

  void advance(uint32_t millisecond_ticks) {
    for(uint32_t tick = 0; tick < millisecond_ticks; ++tick) {
      TIMER1_COMPA_vect();
      Device_loop(&_device);
    }
    _now += millisecond_ticks;
  }

  void advance_until(uint32_t millisecond_tick) {
    if(millisecond_tick > _now) {
      advance(millisecond_tick - _now);
    }
  }

  uint32_t now() {
    return _now;
  }

  void press_button() {
    // TODO bounce/chatter
    _button_stub.set();
    advance(1);
    _button_stub.clear();
    advance(1);
  }

  Spy::Pwm & bell() { return _bell_spy; }

  Stub::Gpio & notify_pin() { return _notify_stub; }

private:
  Stub::Gpio _button_stub;
  Stub::Gpio _notify_stub;
  Spy::Pwm _bell_spy;

  uint32_t _now;

  Gpio & _button;
  Gpio & _notify;
  IPwm & _bell;
  Timer _timer;
  Device _device;
};

#endif //SKELETON_DEVICE_CONTEXT_H
