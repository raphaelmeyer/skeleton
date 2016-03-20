#ifndef SKELETON_PWM_SPY_H
#define SKELETON_PWM_SPY_H

#include <device/ipwm.h>

#include <vector>

namespace Spy { class Pwm; }

struct PwmSpy
{
  IPwm interface;
  Spy::Pwm & spy;
};

namespace Spy
{

class Pwm
{
public:
  Pwm()
    : _events()
    , _impl{{spy_on_on, spy_on_off}, *this}
  {
  }

  static void spy_on_on(IPwm * base) {
    PwmSpy * self = (PwmSpy *)base;
    self->spy._events.push_back(Event{"on"});
  }

  static void spy_on_off(IPwm * base) {
    PwmSpy * self = (PwmSpy *)base;
    self->spy._events.push_back(Event{"off"});
  }

  struct Event
  {
    std::string name;
  };
  std::vector<Event> const & events() { return _events; }

  PwmSpy & impl() { return _impl; }

private:
  std::vector<Event> _events;
  PwmSpy _impl;
};

} // namespace

#endif //SKELETON_PWM_SPY_H
