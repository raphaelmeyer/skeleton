#include <gmock/gmock.h>

#include <device/system_tick.h>

#include <avr/interrupt.h>
#include <avr/io.h>

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

TEST(The_system_tick, uses_hw_timer_1_in_ctc_mode)
{
  TCCR1A = 0x00;
  TCCR0B = 0x00;

  SystemTick_init();

  ASSERT_THAT(TCCR1A, Eq(0x00));
  ASSERT_THAT(TCCR1B & 0xF8, Eq(0x08));

  TCCR1A = 0xFF;
  TCCR0B = 0xFF;

  SystemTick_init();

  ASSERT_THAT(TCCR1A, Eq(0x00));
  ASSERT_THAT(TCCR1B & 0xF8, Eq(0x08));
}

TEST(The_system_tick, is_configured_to_one_millisecond)
{
  TCCR0B = 0;
  OCR1A = 0;

  SystemTick_init();

  ASSERT_THAT(TCCR1B & 0x03, Eq(0x01));
  ASSERT_THAT(OCR1A, Eq(7999));
}

TEST(The_system_tick, notifies_a_registered_observer_with_each_tick)
{
  Spy spy;

  SystemTick_init();
  SystemTick_register(notify_spy, &spy);

  TIMER1_COMPA_vect();
  ASSERT_THAT(spy.called, Eq(1));

  TIMER1_COMPA_vect();
  ASSERT_THAT(spy.called, Eq(2));
}

TEST(The_system_tick, notifies_all_registered_observers)
{
  Spy spy;
  Spy another_spy;

  SystemTick_init();
  SystemTick_register(notify_spy, &spy);
  SystemTick_register(notify_spy, &another_spy);

  TIMER1_COMPA_vect();
  ASSERT_THAT(spy.called, Eq(1));
  ASSERT_THAT(another_spy.called, Eq(1));
}

TEST(The_system_tick, ignores_new_observers_after_two_observers_have_registered)
{
  Spy spy;
  Spy another_spy;
  Spy one_too_many;

  SystemTick_init();
  SystemTick_register(notify_spy, &spy);
  SystemTick_register(notify_spy, &another_spy);
  SystemTick_register(notify_spy, &one_too_many);

  TIMER1_COMPA_vect();
  ASSERT_THAT(spy.called, Eq(1));
  ASSERT_THAT(another_spy.called, Eq(1));
  ASSERT_THAT(one_too_many.called, Eq(0));
}

} // namespace
