#ifndef SKELETON_PWM_SPY_H
#define SKELETON_PWM_SPY_H

#include <device/pwm.h>

#include <vector>

class PwmSpy
{
public:
  PwmSpy()
    : _events()
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
