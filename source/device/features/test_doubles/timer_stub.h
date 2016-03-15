#ifndef SKELETON_TIMER_SPY_H
#define SKELETON_TIMER_SPY_H

#include <device/itimer.h>

#include <vector>
#include <string>

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
    , _events()
    , _state(State::Idle)
  {
  }

  static void start(ITimer * base, uint32_t milliseconds) {
    TimerStub * self = (TimerStub *)base;
    self->stub.start(milliseconds);
  }

  static void stop(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    self->stub.stop();
  }

  static bool expired(ITimer * base) {
    TimerStub * self = (TimerStub *)base;
    return self->stub.expired();
  }

  void start(uint32_t milliseconds) {
    _events.push_back("start");
    _state = State::Running;
  }

  void stop() {
    _events.push_back("stop");
    _state = State::Idle;
  }

  bool expired() {
    return (State::Expired == _state);
  }

  void expire() {
    if(State::Running == _state) {
      _state = State::Expired;
    }
  }

  std::vector<std::string> const & events() { return _events; }
  TimerStub & impl() { return _impl; }

  enum class State { Idle, Running, Expired };

private:
  TimerStub _impl;
  std::vector<std::string> _events;
  State _state;
};

} // namespace

#endif //SKELETON_TIMER_SPY_H
