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
  self->timer = 0;
  self->notify = notify;

  self->state = Device_Idle;

  Timer_init(&self->bell_timer);
  Timer_init(&self->notify_timer);

  Gpio_set_direction(button, Direction_Input);
  Gpio_set_direction(notify, Direction_Output);

  sei();
}

void Device_loop(struct Device * self)
{
  if(Device_Idle == self->state) {
    if(Signal_High == Gpio_get_signal(self->button)) {
      Timer_start(&self->bell_timer, 1000);
      Timer_start(&self->notify_timer, 20);
      Pwm_on(self->bell);
      Gpio_set_signal(self->notify, Signal_High);
      self->state = Device_Ringing;
    }
  } else if(Device_Ringing == self->state) {
    if(Timer_expired(&self->bell_timer)) {
      Pwm_off(self->bell);
      self->state = Device_Idle;
    }
    if(Timer_expired(&self->notify_timer))
    {
      Gpio_set_signal(self->notify, Signal_Low);
    }
  }
}
