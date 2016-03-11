#ifndef SKELETON_PWM_SPY_H_H
#define SKELETON_PWM_SPY_H_H

#include <device/ipwm.h>

namespace {

struct PwmSpy
{
  IPwm interface;

  bool turned_on;
  uint32_t called_on;
  uint32_t called_off;

  PwmSpy()
    : interface{on, off}
    , turned_on(false)
    , called_on(0)
    , called_off(0)
  {
  }

  static void on(IPwm * base)
  {
    PwmSpy * self = (PwmSpy *)base;
    self->turned_on = true;
    ++self->called_on;
  }

  static void off(IPwm * base)
  {
    PwmSpy * self = (PwmSpy *)base;
    self->turned_on = false;
    ++self->called_off;
  }
};

} // namespace

#endif //SKELETON_PWM_SPY_H_H
