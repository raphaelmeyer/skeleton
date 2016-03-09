#include "device/device.h"

#include "device/pwm.h"
#include "device/gpio.h"
#include "device/timer.h"

void Device_init(struct Device * self, struct IPwm * bell, struct Gpio * button, struct ITimer * timer)
{
  self->bell = bell;
  self->button = button;
  self->timer = timer;

  Gpio_set_direction(button, Direction_Input);
}

void Device_loop(struct Device * self)
{
  if(Signal_High == Gpio_get_signal(self->button)) {
    Timer_start(self->timer);
    Pwm_on(self->bell);
  }
}
