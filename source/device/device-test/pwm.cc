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
  ASSERT_TRUE(DDRD);
}

} // namespace
