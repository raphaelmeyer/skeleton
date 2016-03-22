#include <gmock/gmock.h>

#include <device/gpio.h>

#include <avr/io.h>

#include "pretty_print.h"

using namespace ::testing;

namespace
{

class An_input_gpio : public Test
{
protected:
  An_input_gpio()
    : gpio()
    , port(PINB)
    , ddr(DDRB)
    , pin(Pin_3)
  {
  }

  virtual void SetUp() override final {
    port = 0;
    ddr = 0xFF;

    Gpio_init(&gpio, Port_B, Pin_3);
    Gpio_set_direction(&gpio, Direction_Input);
  }

  Gpio gpio;

  uint8_t volatile & port;
  uint8_t volatile & ddr;
  uint8_t const pin;
};

TEST_F(An_input_gpio, clears_the_direction_bit)
{
  bool const ddr_bit = (ddr & (1 << pin)) != 0;
  ASSERT_FALSE(ddr_bit);
}

TEST_F(An_input_gpio, returns_high_when_its_pin_is_set)
{
  port = (1 << pin);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_High));
}

TEST_F(An_input_gpio, returns_low_when_its_pin_is_not_set)
{
  port = ~(1 << pin);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Low));
}

TEST_F(An_input_gpio, is_bound_to_a_single_pin)
{
  port = 0x00;
  port &= ~(1 << pin);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Low));
  port |= (1 << pin);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_High));

  port = 0xFF;
  port &= ~(1 << pin);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Low));
  port |= (1 << pin);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_High));
}


class An_output_gpio : public Test
{
protected:
  An_output_gpio()
    : gpio()
    , port(PORTD)
    , ddr(DDRD)
    , pin(1)
  {
  }

  virtual void SetUp() override final {
    port = 0xFF;
    ddr = 0;

    Gpio_init(&gpio, Port_D, Pin_1);
    Gpio_set_direction(&gpio, Direction_Output);
  }

  Gpio gpio;

  uint8_t volatile & port;
  uint8_t volatile & ddr;
  uint8_t const pin;
};

TEST_F(An_output_gpio, sets_the_direction_bit)
{
  bool const ddr_bit = (ddr & (1 << pin)) != 0;
  ASSERT_TRUE(ddr_bit);
}

TEST_F(An_output_gpio, is_low_after_configuration)
{
  ASSERT_THAT(port & (1 << pin), Eq(0));
}

TEST_F(An_output_gpio, sets_its_pin_when_set_to_high)
{
  port = 0x00;
  Gpio_set_signal(&gpio, Signal_High);
  ASSERT_THAT(port & (1 << pin), Not(Eq(0)));
}

TEST_F(An_output_gpio, clears_its_pin_when_set_to_low)
{
  port = 0xFF;
  Gpio_set_signal(&gpio, Signal_Low);
  ASSERT_THAT(port & (1 << pin), Eq(0));
}

TEST_F(An_output_gpio, is_bound_to_a_single_pin)
{
  port = 0x00;
  Gpio_set_signal(&gpio, Signal_High);
  ASSERT_THAT(port, Eq(1 << pin));
  Gpio_set_signal(&gpio, Signal_Low);
  ASSERT_THAT(port, Eq(0));

  port = 0xFF;
  Gpio_set_signal(&gpio, Signal_High);
  ASSERT_THAT(port, Eq(0xFF));
  Gpio_set_signal(&gpio, Signal_Low);
  ASSERT_THAT(port, Eq(0xFF & ~(1 << pin)));
}

class A_gpio : public Test
{
protected:
  A_gpio()
    : gpio()
    , input(PINC)
    , output(PORTC)
    , ddr(DDRC)
    , pin(5)
  {
  }

  virtual void SetUp() override final {
    Gpio_init(&gpio, Port_C, Pin_5);
  }

  Gpio gpio;

  uint8_t volatile & input;
  uint8_t volatile & output;
  uint8_t volatile & ddr;
  uint8_t const pin;
};

TEST_F(A_gpio, sets_the_direction_bit_when_the_direction_is_changed_from_input_to_output)
{
  Gpio_set_direction(&gpio, Direction_Input);
  Gpio_set_direction(&gpio, Direction_Output);

  bool const ddr_bit = (ddr & (1 << pin)) != 0;
  ASSERT_TRUE(ddr_bit);
}

TEST_F(A_gpio, clears_the_direction_bit_when_the_direction_is_changed_from_output_to_input)
{
  Gpio_set_direction(&gpio, Direction_Output);
  Gpio_set_direction(&gpio, Direction_Input);

  bool const ddr_bit = (ddr & (1 << pin)) != 0;
  ASSERT_FALSE(ddr_bit);
}

TEST_F(A_gpio, returns_undefined_if_not_configured_as_input)
{
  input = 0x00;

  Gpio_set_direction(&gpio, Direction_Undefined);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Undefined));

  Gpio_set_direction(&gpio, Direction_Output);
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Undefined));
}

TEST_F(A_gpio, has_no_direction_set_after_initialisation)
{
  ASSERT_THAT(Gpio_get_signal(&gpio), Eq(Signal_Undefined));
}

TEST_F(A_gpio, does_not_set_pin_when_not_configured_as_output)
{
  output = 0x00;
  Gpio_set_signal(&gpio, Signal_High);
  ASSERT_THAT(output, Eq(0));

  output = 0xFF;
  Gpio_set_signal(&gpio, Signal_Low);
  ASSERT_THAT(output, Eq(0xFF));
}

TEST(Input_gpios, are_bound_to_a_certain_port)
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



} // namespace
