#include <gmock/gmock.h>

#include "timer_stub.h"

using namespace ::testing;

namespace
{

TEST(Timer_base, forwards_start_to_the_concrete_implementation)
{
  TimerStub timer;

  Timer_start((ITimer *)&timer);

  ASSERT_THAT(timer.called_start, Eq(1));
}

} // namespace

