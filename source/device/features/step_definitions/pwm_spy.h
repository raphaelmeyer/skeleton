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
    _impl.interface.on = PwmSpy::on;
    _impl.interface.off = PwmSpy::off;
  }

  static void on(IPwm * base, uint16_t frequency)
  {
    PwmStruct * self = (PwmStruct *)base;
    self->spy.on(frequency);
  }

  void on(uint16_t frequency)
  {
    _events.push_back(Event{"on"});
  }

  static void off(IPwm * base)
  {
    PwmStruct * self = (PwmStruct *)base;
    self->spy.off();
  }

  void off()
  {
    _events.push_back(Event{"off"});
  }

  struct Event{
    std::string name;
    // time
  };
  std::vector<Event> const & events() { return _events; }

  Pwm & impl() { return _impl; }

private:
  std::vector<Event> _events;
  Pwm _impl;
};

#endif //SKELETON_PWM_SPY_H
