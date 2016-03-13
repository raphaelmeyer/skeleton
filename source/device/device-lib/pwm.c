#include "device/pwm.h"

#include "device/io.h"

#include <avr/io.h>

void on(struct IPwm * base);

void Pwm_init(struct Pwm * self)
{
  self->interface.on = on;
  set_bit(&DDRD, 6);
}

void on(struct IPwm * base)
{

}
