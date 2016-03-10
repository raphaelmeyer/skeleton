#ifndef SKELETON_TIMER_STUB_H
#define SKELETON_TIMER_STUB_H

#include <device/timer.h>

struct TimerStub
{
  enum State {
    Idle, Running, Expired
  };

  ITimer interface;
  State state;

  TimerStub()
    : interface{start, stop, expired}
    , state(Idle)
  {
  }

  static void start(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    self->state = Running;
  }
  static void stop(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    self->state = Idle;
  }
  static bool expired(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    return (self->state == Expired);
  }
};

#endif //SKELETON_TIMER_STUB_H
