#include <gmock/gmock.h>

#include <device/system_tick.h>

#include <avr/interrupt.h>

using namespace ::testing;

namespace
{

struct Spy {
  uint32_t called;

  Spy() : called(0) {}
};

void notify_spy(void * observer) {
  Spy * spy = (Spy *)observer;
  ++spy->called;
}

TEST(The_system_tick, DISABLED_uses_hw_timer_1)
{
  FAIL();
}

TEST(The_system_tick, DISABLED_is_configured_to_one_millisecond)
{
  FAIL();
}

TEST(The_system_tick, DISABLED_notifies_a_registered_observer_with_each_tick)
{
  Spy spy;

  SystemTick_init();
  SystemTick_register(notify_spy, &spy);

  TIMER1_COMPA_vect();
  ASSERT_THAT(spy.called, Eq(1));

  // TIMER1_COMPA_vect();
  // ASSERT_THAT(spy.called, Eq(2));
}

TEST(The_system_tick, DISABLED_notifies_all_registered_observers)
{
  FAIL();
}

TEST(The_system_tick, DISABLED_supports_up_to_two_observers)
{
  FAIL();
}

TEST(The_system_tick, DISABLED_ignores_observers_after_two_observers_have_registered)
{
  FAIL();
}

} // namespace
