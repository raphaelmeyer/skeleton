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

TEST(The_pwm, sets_compare_match_register_for_440Hz)
{
  // f = 16000000 / (2 * N * (1 + OCR0A))
  // OCR0A = 8000000 / (f * N) - 1

  Pwm testee;

  OCR0A = 0;

  Pwm_init(&testee);
  Pwm_on((IPwm *)&testee);

  uint8_t const ocr_440_hz = 70;
  ASSERT_THAT(OCR0A, Eq(ocr_440_hz));
}

TEST(The_pwm, sets_mode_to_toggle_at_compare_match)
{
  Pwm testee;

  TCCR0A = 0;
  TCCR0B = 0;

  uint8_t const tccr0a_com0a_mask = 0xC0;
  uint8_t const tccr0a_wgm_mask = 0x03;
  uint8_t const tccr0b_wgm_mask = 0x08;

  uint8_t const tccr0a_com0a = 0x40;
  uint8_t const tccr0a_wgm = 0x03;
  uint8_t const tccr0b_wgm = 0x08;

  Pwm_init(&testee);
  Pwm_on((IPwm *)&testee);

  uint8_t const actual_tccr0a_com0a = TCCR0A & tccr0a_com0a_mask;
  uint8_t const actual_tccr0a_wgm = TCCR0A & tccr0a_wgm_mask;
  uint8_t const actual_tccr0b_wgm = TCCR0B & tccr0b_wgm_mask;

  ASSERT_THAT(actual_tccr0a_com0a, Eq(tccr0a_com0a));
  ASSERT_THAT(actual_tccr0a_wgm, Eq(tccr0a_wgm));
  ASSERT_THAT(actual_tccr0b_wgm, Eq(tccr0b_wgm));
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
