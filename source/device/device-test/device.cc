#include <gmock/gmock.h>

#include <device/gpio.h>

#include "pretty_print.h"

using namespace ::testing;

uint8_t PINB = 0;
uint8_t PINC = 0;
uint8_t PIND = 0;

namespace
{

TEST(An_input_gpio, returns_high_when_its_pin_is_set)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction((IGpio *)&gpio, Direction_Input);

  PINB = (1 << 3);
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_High));
}

TEST(An_input_gpio, returns_low_when_its_pin_is_not_set)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction((IGpio *)&gpio, Direction_Input);

  PINB = 0;
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_Low));
}

TEST(An_input_gpio, is_bound_to_a_single_pin)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction((IGpio *)&gpio, Direction_Input);

  PINB = ~(1 << 3);
  ASSERT_THAT(Gpio_get_signal((IGpio *)&gpio), Eq(Signal_Low));
}

TEST(An_input_gpio, is_bound_to_a_certain_port)
{
  Gpio pin_c_4;
  Gpio_init(&pin_c_4, Port_C, Pin_4);
  Gpio_set_direction((IGpio *)&pin_c_4, Direction_Input);

  Gpio pin_c_5;
  Gpio_init(&pin_c_5, Port_C, Pin_5);
  Gpio_set_direction((IGpio *)&pin_c_5, Direction_Input);

  Gpio pin_d_4;
  Gpio_init(&pin_d_4, Port_D, Pin_4);
  Gpio_set_direction((IGpio *)&pin_d_4, Direction_Input);

  Gpio pin_d_5;
  Gpio_init(&pin_d_5, Port_D, Pin_5);
  Gpio_set_direction((IGpio *)&pin_d_5, Direction_Input);

  PINB = 0;
  PINC = (1 << 4);
  PIND = (1 << 5);

  ASSERT_THAT(Gpio_get_signal((IGpio *)&pin_c_4), Eq(Signal_High));
  ASSERT_THAT(Gpio_get_signal((IGpio *)&pin_c_5), Eq(Signal_Low));
  ASSERT_THAT(Gpio_get_signal((IGpio *)&pin_d_4), Eq(Signal_Low));
  ASSERT_THAT(Gpio_get_signal((IGpio *)&pin_d_5), Eq(Signal_High));
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
