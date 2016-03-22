#include <gmock/gmock.h>

#include <device/gpio.h>

#include <avr/io.h>

#include "pretty_print.h"

using namespace ::testing;

namespace
{

TEST(An_input_gpio, returns_high_when_its_pin_is_set)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction(&gpio, Direction_Input);

  PINB = (1 << 3);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_High));
}

TEST(An_input_gpio, returns_low_when_its_pin_is_not_set)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction(&gpio, Direction_Input);

  PINB = 0;
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Low));
}

TEST(An_input_gpio, is_bound_to_a_single_pin)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);
  Gpio_set_direction(&gpio, Direction_Input);

  PINB = ~(1 << 3);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Low));
}

TEST(An_input_gpio, is_bound_to_a_certain_port)
{
  Gpio pin_c_4;
  Gpio_init(&pin_c_4, Port_C, Pin_4);
  Gpio_set_direction(&pin_c_4, Direction_Input);

  Gpio pin_c_5;
  Gpio_init(&pin_c_5, Port_C, Pin_5);
  Gpio_set_direction(&pin_c_5, Direction_Input);

  Gpio pin_d_4;
  Gpio_init(&pin_d_4, Port_D, Pin_4);
  Gpio_set_direction(&pin_d_4, Direction_Input);

  Gpio pin_d_5;
  Gpio_init(&pin_d_5, Port_D, Pin_5);
  Gpio_set_direction(&pin_d_5, Direction_Input);

  PINB = 0;
  PINC = (1 << 4);
  PIND = (1 << 5);

  ASSERT_THAT(Gpio_get_signal(&pin_c_4), Eq(Signal_High));
  ASSERT_THAT(Gpio_get_signal(&pin_c_5), Eq(Signal_Low));
  ASSERT_THAT(Gpio_get_signal(&pin_d_4), Eq(Signal_Low));
  ASSERT_THAT(Gpio_get_signal(&pin_d_5), Eq(Signal_High));
}

TEST(An_input_gpio, clears_the_direction_bit)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_D, Pin_6);
  DDRD = 0xFF;

  Gpio_set_direction(&gpio, Direction_Input);

  bool const ddr_bit = DDRD & (1 << 6);
  ASSERT_FALSE(ddr_bit);
}

TEST(An_output_gpio, sets_the_direction_bit_to_one)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_D, Pin_6);
  DDRD = 0;

  Gpio_set_direction(&gpio, Direction_Output);

  bool const ddr_bit = DDRD & (1 << 6);
  ASSERT_TRUE(ddr_bit);
}

TEST(A_gpio, sets_the_direction_bit_when_the_direction_is_changed_from_input_to_output)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_2);

  Gpio_set_direction(&gpio, Direction_Input);
  Gpio_set_direction(&gpio, Direction_Output);

  bool const ddr_bit = DDRB & (1 << 2);
  ASSERT_TRUE(ddr_bit);
}

TEST(A_gpio, clears_the_direction_bit_when_the_direction_is_changed_from_output_to_input)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_7);

  Gpio_set_direction(&gpio, Direction_Output);
  Gpio_set_direction(&gpio, Direction_Input);

  bool const ddr_bit = DDRB & (1 << 7);
  ASSERT_FALSE(ddr_bit);
}

TEST(A_gpio, returns_undefined_if_not_configured_as_input)
{
  Gpio gpio;
  Gpio_init(&gpio, Port_B, Pin_3);

  PINB = 0x00;
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Undefined));

  Gpio_set_direction(&gpio, Direction_Output);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Undefined));
}

TEST(An_output_gpio, DISABLED_todo)
{
  FAIL();
}

} // namespace
