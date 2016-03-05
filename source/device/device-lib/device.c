#include "device/device.h"

#include "device/pwm.h"
#include "device/gpio.h"

void Device_init(struct Device * self, struct IPwm * bell, struct Gpio * button)
{
  self->bell = bell;
  self->button = button;

  Gpio_set_direction(button, Direction_Input);
}

void Device_loop(struct Device * self)
{
}
