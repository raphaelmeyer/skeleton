#include "device/device.h"

#include "device/gpio.h"
#include "device/ipwm.h"

#include <avr/interrupt.h>

bool button_pushed(struct Device * self);
bool done_ringing(struct Device * self);

void Device_init(struct Device * self, struct IPwm * bell, struct Gpio * button, struct Gpio * notify)
{
  self->bell = bell;
  self->button = button;
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
  switch(self->state) {
    default:
      break;

    case Device_Idle:
      if(button_pushed(self)) {
        self->state = Device_Ringing;
      }
      break;

    case Device_Ringing:
      if(done_ringing(self)) {
        self->state = Device_Idle;
      }
      break;
  }
}

bool done_ringing(struct Device * self) {
  if(Timer_expired(&self->notify_timer))
  {
    Gpio_set_signal(self->notify, Signal_Low);
  }
  if(Timer_expired(&self->bell_timer)) {
    Pwm_off(self->bell);
    return true;
  }
  return false;
}

bool button_pushed(struct Device * self)
{
  if(Signal_High == Gpio_get_signal(self->button)) {
    Timer_start(&self->bell_timer, 1000);
    Timer_start(&self->notify_timer, 20);
    Pwm_on(self->bell);
    Gpio_set_signal(self->notify, Signal_High);
    return true;
  }
  return false;
}
