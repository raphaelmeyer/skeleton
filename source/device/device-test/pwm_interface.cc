#include <gmock/gmock.h>

#include "pwm_spy.h"

using namespace ::testing;

namespace
{

TEST(Pwm_base, forwards_on_to_the_concrete_implementation)
{
  PwmSpy pwm;

  Pwm_on((IPwm *)&pwm);

  ASSERT_THAT(pwm.called_on, Eq(1));
}

TEST(Pwm_base, forwards_off_to_the_concrete_implementation)
{
  PwmSpy pwm;

  Pwm_off((IPwm *)&pwm);

  ASSERT_THAT(pwm.called_off, Eq(1));
}

} // namespace
