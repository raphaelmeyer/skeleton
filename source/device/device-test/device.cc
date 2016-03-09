#include <gmock/gmock.h>

#include <device/device.h>
#include <device/gpio.h>
#include <device/pwm.h>
#include <device/timer.h>

#include <avr/io.h>

using namespace ::testing;

namespace
{

struct PwmStub
{
  IPwm interface;
  bool turned_on;

  static void on(IPwm * base)
  {
    PwmStub * self = (PwmStub *)base;
    self->turned_on = true;
  }
};

struct TimerSpy
{
  enum State {
    Idle, Running, Expired
  };

  ITimer interface;
  State state;

  static void start(ITimer * base) {
    TimerSpy * self = (TimerSpy *)base;
    self->state = Running;
  }
  static void stop(ITimer * base) {
    TimerSpy * self = (TimerSpy *)base;
    self->state = Idle;
  }
  static bool expired(ITimer * base) {
    TimerSpy * self = (TimerSpy *)base;
    return (self->state == Expired);
  }
};

TEST(The_device, configures_the_button_pin_as_an_input)
{
  Gpio button;
  Device testee;

  Gpio_init(&button, Port_D, Pin_4);
  DDRD = 0xFF;

  Device_init(&testee, nullptr, &button);

  bool const ddr_bit = DDRD & (1 << 4);
  ASSERT_FALSE(ddr_bit);
}

TEST(The_device, turns_on_the_bell_pwm_when_the_button_signal_is_high)
{
  Gpio button;
  PwmStub bell{{PwmStub::on, nullptr}, false};
  Device testee;

  Gpio_init(&button, Port_C, Pin_2);
  Device_init(&testee, (IPwm *)&bell, &button);

  PINC = (1 << 2);
  Device_loop(&testee);

  ASSERT_TRUE(bell.turned_on);
}

TEST(The_device, DISABLED_sets_a_timer_to_rings_the_bell_for_a_certain_time)
{
  Gpio button;
  TimerSpy timer{{}, TimerSpy::Idle};
  PwmStub bell{{PwmStub::on, nullptr}, false};
  Device testee;

  Gpio_init(&button, Port_C, Pin_2);
  Device_init(&testee, (IPwm *)&bell, &button);

  PINC = (1 << 2);
  Device_loop(&testee);

  ASSERT_THAT(timer.state, Eq(TimerSpy::Running));
}

TEST(The_device, DISABLED_turns_the_bell_off_after_the_timer_expires)
{
  //timer.state = TimerSpy::Expired;
  //Device_loop(&testee);
  //ASSERT_FALSE(bell.turned_on);

  FAIL();
}

} // namespace
