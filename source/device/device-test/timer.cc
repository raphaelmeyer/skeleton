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

TEST(A_timer, is_not_expired_after_start_until_xxx)
{
  // Timer_init()
  // Timer_start(3);
  // ASSERT_FALSE(Timer_expired())
  // TickStub.notify()
  // ASSERT_FALSE(Timer_expired())

  FAIL();
}

TEST(A_timer, DISABLED_expires_after_the_given_number_of_milliseconds)
{
  // Timer_init()
  // Timer_start(3);
  // ASSERT_FALSE(Timer_expired())
  // TickStub.notify()
  // TickStub.notify()
  // TickStub.notify()
  // ASSERT_TRUE(Timer_expired())

  FAIL();
}

TEST(A_timer, DISABLED_is_not_expired_if_it_was_stopped)
{
  FAIL();
}

} // namespace
