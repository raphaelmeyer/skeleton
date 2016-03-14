#include "device/pwm.h"

#include "device/io.h"

#include <avr/io.h>

static uint8_t const Prescaler_256 = 0x04;

void on(struct IPwm * base);

void Pwm_init(struct Pwm * self)
{
  self->interface.on = on;
  set_bit(&DDRD, 6);
}

void on(struct IPwm * base)
{
  TCCR0A = 0x43;
  TCCR0B = 0x08 | Prescaler_256;
  OCR0A = 70;
}
