#include <gmock/gmock.h>

#include <device/gpio.h>

using namespace ::testing;

uint8_t PORTB = 0;

TEST(A_gpio, configured_as_input_returns_its_pin_signal_state)
{
  Gpio gpio;
  Gpio_init(&gpio);
  Gpio_set_direction((IGpio *)&gpio, Direction_Input);

  PORTB = 0x00;
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_Low));

  PORTB = 0x01;
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_High));
}

