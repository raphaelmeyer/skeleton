#include <gmock/gmock.h>

#include <device/device.h>

#include <device/gpio.h>
#include <device/pwm.h>

#include <avr/io.h>

using namespace ::testing;

namespace
{

TEST(The_device, DISABLED_rings_the_bell_when_the_button_signal_is_high)
{
  IPwm bell;
  Gpio button;
  Device testee;

  Gpio_init(&button, Port_C, Pin_2);
  Device_init(&testee, &bell, &button);

  uint8_t TODO_PWM_REG = 0;
  PINC = (1 << 2);

  Device_loop(&testee);

  ASSERT_THAT(TODO_PWM_REG, Eq(0x2A));
}

} // namespace
