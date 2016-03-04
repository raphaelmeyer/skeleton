#include "device/device.h"

#include "device/pwm.h"
#include "device/gpio.h"

void Device_init(struct Device * self, struct IPwm * bell, struct Gpio * button)
{
  self->bell = bell;
  self->button = button;
}

void Device_loop(struct Device * self)
{
  if(Gpio_get_signal(self->button) == Signal_High) {
    Pwm_on(self->bell);
  }
}
