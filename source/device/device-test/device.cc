#include <gmock/gmock.h>

#include <device/device.h>
#include <device/gpio.h>
#include <device/timer.h>
#include <device/system_tick.h>

#include <avr/io.h>

#include "pwm_spy.h"
#include "seams_interrupt.h"

using namespace ::testing;

namespace
{

class The_device : public Test
{
protected:
  The_device()
    : button()
    , bell()
    , testee()
    , button_ddr(DDRC)
    , button_port(PINC)
    , button_pin(2)
    , notify_ddr(DDRD)
    , notify_port(PORTD)
    , notify_pin(5)
  {
  }

  virtual void SetUp() {
    SystemTick_init();

    Gpio_init(&button, Port_C, Pin_2);
    Gpio_init(&notify, Port_D, Pin_5);
  }

  void button_set() {
    button_port = (1 << button_pin);
  }

  void button_clear() {
    button_port = 0;
  }

  bool notify_is_set() {
    return (notify_port & (1 << notify_pin)) != 0;
  }

  Gpio button;
  Gpio notify;
  PwmSpy bell;
  Device testee;

  uint8_t volatile & button_ddr;
  uint8_t volatile & button_port;
  uint8_t const button_pin;

  uint8_t volatile & notify_ddr;
  uint8_t volatile & notify_port;
  uint8_t const notify_pin;
};

TEST_F(The_device, configures_the_button_pin_as_an_input)
{
  button_ddr = 0xFF;

  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  bool const ddr_bit = (button_ddr & (1 << button_pin)) != 0;
  ASSERT_FALSE(ddr_bit);
}

TEST_F(The_device, enables_the_interrupts)
{
  interrupt_spy.enabled = false;

  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  ASSERT_TRUE(interrupt_spy.enabled);
}

TEST_F(The_device, turns_on_the_bell_pwm_when_the_button_signal_is_high)
{
  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  button_set();
  Device_loop(&testee);

  ASSERT_TRUE(bell.turned_on);
}

TEST_F(The_device, does_not_ring_the_bell_when_the_button_signal_is_low)
{
  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  button_clear();
  Device_loop(&testee);

  ASSERT_FALSE(bell.turned_on);
}

TEST_F(The_device, does_not_turn_on_pwm_again_when_the_bell_is_already_ringing)
{
  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  button_set();
  Device_loop(&testee);
  Device_loop(&testee);
  Device_loop(&testee);

  ASSERT_TRUE(bell.turned_on);
  ASSERT_THAT(bell.called_on, Eq(1));
}

TEST_F(The_device, turns_the_bell_off_after_1000_milliseconds)
{
  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  button_set();
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

TEST_F(The_device, configures_the_notify_pin_as_output)
{
  notify_ddr = 0;

  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  bool const ddr_bit = (notify_ddr & (1 << notify_pin)) != 0;
  ASSERT_TRUE(ddr_bit);
}

TEST_F(The_device, sets_the_notification_pin_to_high_when_the_bell_rings)
{
  notify_port = 0;

  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  button_set();
  Device_loop(&testee);

  ASSERT_TRUE(notify_is_set());
}

TEST_F(The_device, resets_the_notification_pin_to_low_after_20_ms)
{
  Device_init(&testee, (IPwm *)&bell, &button, &notify);

  button_set();
  Device_loop(&testee);

  uint32_t const pulse_time = 20;
  for(uint32_t i = 0; i < pulse_time - 1; ++i) {
    TIMER1_COMPA_vect();
    Device_loop(&testee);
  }
  ASSERT_TRUE(notify_is_set());

  TIMER1_COMPA_vect();
  Device_loop(&testee);
  ASSERT_FALSE(notify_is_set());
}

} // namespace
