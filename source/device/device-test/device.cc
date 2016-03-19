#include <gmock/gmock.h>

#include <device/device.h>
#include <device/gpio.h>
#include <device/timer.h>
#include <device/system_tick.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "pwm_spy.h"

using namespace ::testing;

namespace
{

class The_device : public Test
{
protected:
  Gpio button;
  PwmSpy bell;
  Timer timer;
  Device testee;
};

TEST_F(The_device, configures_the_button_pin_as_an_input)
{
  Gpio_init(&button, Port_D, Pin_4);
  Timer_init(&timer);

  DDRD = 0xFF;

  Device_init(&testee, (IPwm *)&bell, &button, &timer);

  bool const ddr_bit = DDRD & (1 << 4);
  ASSERT_FALSE(ddr_bit);
}

TEST_F(The_device, turns_on_the_bell_pwm_when_the_button_signal_is_high)
{
  Gpio_init(&button, Port_C, Pin_2);
  Timer_init(&timer);

  Device_init(&testee, (IPwm *)&bell, &button, &timer);

  PINC = (1 << 2);
  Device_loop(&testee);

  ASSERT_TRUE(bell.turned_on);
}

TEST_F(The_device, does_not_ring_the_bell_when_the_button_signal_is_low)
{
  Gpio_init(&button, Port_C, Pin_2);
  Timer_init(&timer);

  Device_init(&testee, (IPwm *)&bell, &button, &timer);

  PINC = 0;
  Device_loop(&testee);

  ASSERT_FALSE(bell.turned_on);
}

TEST_F(The_device, does_not_turn_on_pwm_again_when_the_bell_is_already_ringing)
{
  Gpio_init(&button, Port_C, Pin_2);
  Timer_init(&timer);

  Device_init(&testee, (IPwm *)&bell, &button, &timer);

  PINC = (1 << 2);
  Device_loop(&testee);
  Device_loop(&testee);
  Device_loop(&testee);

  ASSERT_TRUE(bell.turned_on);
  ASSERT_THAT(bell.called_on, Eq(1));
}

TEST_F(The_device, turns_the_bell_off_after_1000_milliseconds)
{
  SystemTick_init();
  Gpio_init(&button, Port_C, Pin_2);
  Timer_init(&timer);

  Device_init(&testee, (IPwm *)&bell, &button, &timer);

  PINC = (1 << 2);
  Device_loop(&testee);

  uint32_t const ringing_time = 1000;

  for(uint32_t tick = 0; tick < ringing_time - 1; ++tick) {
    TIMER1_COMPA_vect();
    Device_loop(&testee);
  }
  ASSERT_TRUE(bell.turned_on);

  TIMER1_COMPA_vect();
  Device_loop(&testee);
  ASSERT_FALSE(bell.turned_on);
}

TEST(The_device_loop, DISABLED_is_executed_once_per_system_tick)
{
  FAIL();
}

} // namespace
