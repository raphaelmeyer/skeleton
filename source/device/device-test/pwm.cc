#include <gmock/gmock.h>

#include <device/pwm.h>

#include <avr/io.h>

using namespace ::testing;

namespace
{

TEST(The_pwm, configures_its_pin_PD6_as_output)
{
  Pwm testee;

  DDRD = 0;
  Pwm_init(&testee);

  bool const ddr_bit = (DDRD & (1 << 6)) != 0;
  ASSERT_TRUE(ddr_bit);
}

TEST(The_pwm, sets_the_prescaler_to_256)
{
  Pwm testee;

  TCCR0B = 0;

  Pwm_init(&testee);
  Pwm_on((IPwm *)&testee);

  uint8_t const expected_cs = 0x04;
  uint8_t const cs_mask = 0x07;

  uint8_t const actual_cs = TCCR0B & cs_mask;
  ASSERT_THAT(actual_cs, Eq(expected_cs));
}

TEST(The_pwm, DISABLED_sets_compare_match_register_for_440Hz)
{
  // f = 16000000 / (2 * N * (1 + OCR0A))
  // OCR0A = 8000000 / (f * N) - 1;
  ASSERT_THAT(OCR0A, Eq(70));
}

TEST(The_pwm, DISABLED_sets_mode_to_toggle_at_compare_match)
{
  //ASSERT_THAT((TCCR0A & (COM0A1 | COM0A0)), Eq(COM0A0));
  // wgm = ....
  //ASSERT_THAT(wgm, Eq(0x07));
  FAIL();
}

TEST(The_pwm, DISABLED_restores_normal_port_operation_when_turned_off)
{
  //ASSERT_THAT((TCCR0A & (COM0A1 | COM0A0)), Eq(0));
  FAIL();
}

TEST(The_pwm, DISABLED_sets_its_output_to_low_when_turned_off)
{
  // ASSERT_FALSE(PORTD & (1 << 6));
  FAIL();
}


} // namespace
