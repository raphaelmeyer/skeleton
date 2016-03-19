#include <gmock/gmock.h>

#include <device/timer.h>
#include <device/system_tick.h>

#include <avr/interrupt.h>

using namespace ::testing;

namespace
{

class An_initialised_timer : public Test
{
protected:
  virtual void SetUp() {
    SystemTick_init();
    Timer_init(&testee);
  }

  Timer testee;
};

class An_expired_timer : public Test
{
protected:
  virtual void SetUp() {
    SystemTick_init();

    Timer_init(&testee);
    Timer_start(&testee, 1);
    TIMER1_COMPA_vect();
  }

  Timer testee;
};

TEST(A_timer, is_not_expired_just_after_initialisation)
{
  Timer testee;

  SystemTick_init();
  Timer_init(&testee);

  ASSERT_FALSE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, with_a_value_of_zero_expires_immediately)
{
  Timer testee;

  Timer_init(&testee);

  Timer_start(&testee, 0);

  ASSERT_TRUE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, is_not_expired_after_starting_when_the_set_time_has_not_yet_passed)
{
  Timer_start(&testee, 3);
  TIMER1_COMPA_vect();

  ASSERT_FALSE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, expires_after_the_given_number_of_milliseconds)
{
  Timer_start(&testee, 3);
  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();

  ASSERT_TRUE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, is_not_expired_if_it_was_stopped)
{
  Timer_start(&testee, 3);
  TIMER1_COMPA_vect();

  Timer_stop(&testee);
  ASSERT_FALSE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, is_not_expired_even_when_the_time_passed_after_stopping)
{
  Timer_start(&testee, 3);
  TIMER1_COMPA_vect();

  Timer_stop(&testee);

  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();

  ASSERT_FALSE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, is_not_expired_anymore_if_it_is_stopped_after_expiration)
{
  Timer_start(&testee, 2);

  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();

  Timer_stop(&testee);

  ASSERT_FALSE(Timer_expired(&testee));
}

TEST_F(An_initialised_timer, is_restarted_when_started_while_still_running)
{
  Timer_start(&testee, 2);
  TIMER1_COMPA_vect();

  Timer_start(&testee, 3);
  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();
  ASSERT_FALSE(Timer_expired(&testee));

  TIMER1_COMPA_vect();
  ASSERT_TRUE(Timer_expired(&testee));
}

TEST_F(An_expired_timer, is_not_expired_anymore_when_started_again)
{
  Timer_start(&testee, 3);
  ASSERT_FALSE(Timer_expired(&testee));
}

TEST_F(An_expired_timer, expires_after_the_given_time_when_started_again)
{
  Timer_start(&testee, 3);
  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();
  TIMER1_COMPA_vect();

  ASSERT_TRUE(Timer_expired(&testee));
}

} // namespace
