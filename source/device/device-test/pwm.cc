#include <gmock/gmock.h>

#include <device/pwm.h>

using namespace ::testing;

namespace
{

struct PwmSpy
{
  IPwm interface;
  uint32_t called_on;

  static void on(IPwm * base)
  {
    PwmSpy * self = (PwmSpy *)base;
    ++(self->called_on);
  }
};

TEST(Pwm_base, forwards_on_to_the_concrete_implementation)
{
  PwmSpy pwm{{PwmSpy::on, nullptr}, 0};

  Pwm_on((IPwm *)&pwm);

  ASSERT_THAT(pwm.called_on, Eq(1));
}

} // namespace
