#ifndef SKELETON_TIMER_STUB_H
#define SKELETON_TIMER_STUB_H

#include <device/itimer.h>

enum class TimerState {
  Idle, Running, Expired
};

struct TimerStub
{
  ITimer interface;
  TimerState state;

  uint32_t called_start;
  uint32_t called_stop;
  uint32_t called_expired;

  TimerStub()
    : interface{start, stop, expired}
    , state(TimerState::Idle)
    , called_start(0)
    , called_stop(0)
    , called_expired(0)
  {
  }

  static void start(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    ++self->called_start;
    self->state = TimerState::Running;
  }
  static void stop(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    ++self->called_stop;
    self->state = TimerState::Idle;
  }
  static bool expired(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    ++self->called_expired;
    return (self->state == TimerState::Expired);
  }
};

#endif //SKELETON_TIMER_STUB_H
