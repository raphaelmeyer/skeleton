#ifndef SKELETON_PWM_SPY_H_H
#define SKELETON_PWM_SPY_H_H

#include <device/pwm.h>

namespace {

struct PwmSpy
{
  IPwm interface;

  bool turned_on;
  uint32_t called_on;

  PwmSpy()
    : interface{on, nullptr}
    , turned_on(false)
    , called_on{0}
  {
  }

  static void on(IPwm * base)
  {
    PwmSpy * self = (PwmSpy *)base;
    self->turned_on = true;
    ++self->called_on;
  }
};

} // namespace

#endif //SKELETON_PWM_SPY_H_H
