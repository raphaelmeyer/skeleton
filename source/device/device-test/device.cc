#include <gmock/gmock.h>

#include <device/device.h>
#include <device/gpio.h>
#include <device/pwm.h>

#include <avr/io.h>

using namespace ::testing;

namespace
{

struct PwmStub
{
  IPwm interface;
  bool turned_on;

  static void on(IPwm * base)
  {
    PwmStub * self = (PwmStub *)base;
    self->turned_on = true;
  }
};


TEST(The_device, configures_the_button_pin_as_an_input)
{
  Gpio button;
  Device testee;

  Gpio_init(&button, Port_D, Pin_4);
  DDRD = 0xFF;

  Device_init(&testee, nullptr, &button);

  bool const ddr_bit = DDRD & (1 << 4);
  ASSERT_FALSE(ddr_bit);
}

TEST(The_device, DISABLED_turns_on_the_bell_pwm_when_the_button_signal_is_high)
{
  Gpio button;
  PwmStub bell{{PwmStub::on, nullptr}, false};
  Device testee;

  Gpio_init(&button, Port_C, Pin_2);
  Device_init(&testee, (IPwm *)&bell, &button);

  PINC = (1 << 2);
  Device_loop(&testee);

  ASSERT_TRUE(bell.turned_on);
}

} // namespace