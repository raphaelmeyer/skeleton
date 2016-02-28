#ifndef SKELETON_PWM_SPY_H
#define SKELETON_PWM_SPY_H

#include <device/pwm.h>

#include <vector>

class PwmSpy;

struct PwmStruct
{
  IPwm interface;
  PwmSpy & spy;
};

class PwmSpy
{
public:
  PwmSpy()
    : _events()
    , _impl()
  {
    _impl.interface.on_for = PwmSpy::on_for;
  }

  static void on_for(IPwm * base, uint16_t frequency, uint16_t duration)
  {
    PwmStruct * self = (PwmStruct *)base;
    self->spy.on_for(frequency, duration);
  }

  void on_for(uint16_t frequency, uint16_t duration)
  {
    _events.push_back(Event());
  }

  struct Event{};
  std::vector<Event> const & events() { return _events; }

  Pwm & impl() { return _impl; }

private:
  std::vector<Event> _events;
  Pwm _impl;
};

#endif //SKELETON_PWM_SPY_H
