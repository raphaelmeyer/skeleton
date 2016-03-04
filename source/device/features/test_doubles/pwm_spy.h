#ifndef SKELETON_PWM_SPY_H
#define SKELETON_PWM_SPY_H

#include <device/pwm.h>

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
    , _impl{{Pwm::on, Pwm::off}, *this}
  {
  }

  static void on(IPwm * base)
  {
    PwmSpy * self = (PwmSpy *)base;
    self->spy.on();
  }

  void on()
  {
    _events.push_back(Event{"on"});
  }

  static void off(IPwm * base)
  {
    PwmSpy * self = (PwmSpy *)base;
    self->spy.off();
  }

  void off()
  {
    _events.push_back(Event{"off"});
  }

  struct Event
  {
    std::string name;
    // time
  };
  std::vector<Event> const & events() { return _events; }

  PwmSpy & impl() { return _impl; }

private:
  std::vector<Event> _events;
  PwmSpy _impl;
};

} // namespace

#endif //SKELETON_PWM_SPY_H
