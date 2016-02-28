#include <gmock/gmock.h>

#include <device/gpio.h>

using namespace ::testing;

uint8_t PINB = 0;

namespace
{

TEST(An_input_gpio, returns_its_pin_signal_state)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction((IGpio *)&gpio, Direction_Input);

  PINB = 0x00;
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_Low));

  PINB = 0x01;
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_High));
}

TEST(A_gpio, returns_undefined_if_not_configured_as_input)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);

  PINB = 0x00;
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_Undefined));

  Gpio_set_direction((IGpio *)&gpio, Direction_Output);
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_Undefined));
}



} // namespace
