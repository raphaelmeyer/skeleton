#include <gmock/gmock.h>

#include <device/timer.h>

using namespace ::testing;

namespace
{

struct TimerSpy
{
  ITimer interface;
  uint32_t called_start;
  uint32_t called_stop;
  uint32_t called_expired;

  static void start(ITimer * base)
  {
    TimerSpy * self = (TimerSpy *)base;
    ++(self->called_start);
  }
};

TEST(Timer_base, forwards_start_to_the_concrete_implementation)
{
  TimerSpy timer{{TimerSpy::start}, 0, 0, 0};

  Timer_start((ITimer *)&timer);

  ASSERT_THAT(timer.called_start, Eq(1));
}

} // namespace

