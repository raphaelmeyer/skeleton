#include <gmock/gmock.h>

#include "timer_stub.h"

using namespace ::testing;

namespace
{

TEST(Timer_base, forwards_start_to_the_concrete_implementation)
{
  TimerStub timer;

  Timer_start((ITimer *)&timer, 0);

  ASSERT_THAT(timer.called_start, Eq(1));
}

TEST(Timer_base, forwards_the_timer_value_of_start)
{
  TimerStub timer;

  uint32_t const timer_value = 23;

  Timer_start((ITimer *)&timer, timer_value);

  ASSERT_THAT(timer.timer_value, Eq(timer_value));
}

TEST(Timer_base, forwards_expired_to_the_concrete_implementaion)
{
  TimerStub timer;

  Timer_expired((ITimer *)&timer);

  ASSERT_THAT(timer.called_expired, Eq(1));
}

TEST(Timer_base, forwards_update_to_the_concrete_implementaion)
{
  TimerStub timer;

  Timer_update((ITimer *)&timer);

  ASSERT_THAT(timer.called_update, Eq(1));
}

} // namespace

