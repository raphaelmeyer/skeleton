#ifndef SKELETON_TIMER_SPY_H
#define SKELETON_TIMER_SPY_H

#include <device/itimer.h>

#include <vector>

namespace Stub { class Timer; }

struct TimerStub
{
  ITimer interface;
  Stub::Timer & stub;
};

namespace Stub
{

class Timer
{
public:
  Timer()
    : _impl{{start, stop, expired}, *this}
  {
  }

  static void start(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    self->stub.start();
  }

  static void stop(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    self->stub.stop();
  }

  static bool expired(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    return self->stub.expired();
  }

  void start() {
  }

  void stop() {
  }

  bool expired() {
    return false;
  }

private:
  TimerStub _impl;
};

} // namespace

#endif //SKELETON_TIMER_SPY_H
