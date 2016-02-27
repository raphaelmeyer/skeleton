#ifndef SKELETON_PWM_SPY_H
#define SKELETON_PWM_SPY_H

#include <device/pwm.h>

#include <vector>

struct PwmStruct
{
  IPwm interface;
};

class PwmSpy
{
public:
  PwmSpy()
    : _events()
  {
    _impl.interface.on = PwmSpy::on;
    _impl.interface.off = PwmSpy::off;
  }

  static void on(IPwm * base, uint16_t frequency)
  {
  }

  static void off(IPwm * base)
  {
  }

  struct Event{};
  std::vector<Event> const & events() { return _events; }

  Pwm & impl() { return _impl; }

private:
  std::vector<Event> _events;
  Pwm _impl;
};

#endif //SKELETON_PWM_SPY_H
