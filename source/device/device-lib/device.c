#include "device/device.h"

#include "device/gpio.h"
#include "device/ipwm.h"
#include "device/timer.h"

#include <avr/interrupt.h>

void Device_init(
  struct Device * self, struct IPwm * bell, struct Gpio * button, struct Timer * timer,
  struct Gpio * notify)
{
  self->bell = bell;
  self->button = button;
  self->timer = timer;

  self->state = Device_Idle;

  Gpio_set_direction(button, Direction_Input);

  sei();
}

void Device_loop(struct Device * self)
{
  if(Device_Idle == self->state) {
    if(Signal_High == Gpio_get_signal(self->button)) {
      Timer_start(self->timer, 1000);
      Pwm_on(self->bell);
      self->state = Device_Ringing;
    }
  } else if(Device_Ringing == self->state) {
    if(Timer_expired(self->timer)) {
      Pwm_off(self->bell);
      self->state = Device_Idle;
    }
  }
}
