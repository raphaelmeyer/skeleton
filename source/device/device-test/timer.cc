#include <gmock/gmock.h>

#include <device/timer.h>

#include <avr/io.h>

using namespace ::testing;

namespace
{

TEST(A_timer, is_not_expired_after_initialisation)
{
  Timer testee;

  Timer_init(&testee);

  bool const expired = Timer_expired((ITimer *)&testee);
  ASSERT_FALSE(expired);
}

} // namespace
