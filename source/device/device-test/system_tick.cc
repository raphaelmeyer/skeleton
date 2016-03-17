#include <gmock/gmock.h>

#include <device/system_tick.h>

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

TEST(The_system_tick, DISABLED_is_configured_to_one_millisecond)
{
  FAIL();
}

TEST(The_system_tick, DISABLED_notifies_a_registered_observer_with_each_tick)
{
  Spy spy;

  SystemTick_init();
  SystemTick_register(notify_spy, &spy);

  // interrupt
  ASSERT_THAT(spy.called, Eq(1));

  // interrupt
  // ASSERT_THAT(spy.called, Eq(2));
}

TEST(The_system_tick, DISABLED_notifies_all_registered_observers)
{
  FAIL();
}

} // namespace
