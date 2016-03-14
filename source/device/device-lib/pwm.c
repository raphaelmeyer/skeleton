#include "device/pwm.h"

#include "device/io.h"

#include <avr/io.h>

static void on(struct IPwm * base);
static void off(struct IPwm * base);

void Pwm_init(struct Pwm * self)
{
  self->interface.on = on;
  self->interface.off = off;

  self->output_pin = 6;

  set_bit(&DDRD, self->output_pin);
}

static void on(struct IPwm * base)
{
  uint8_t const Compare_440_Hz = 70;
  uint8_t const Prescaler_256 = 0x04;

  TCCR0A = bit_value(COM0A0) | bit_value(WGM01) | bit_value(WGM00);
  TCCR0B = bit_value(WGM02) | Prescaler_256;
  OCR0A = Compare_440_Hz;
}

static void off(struct IPwm * base)
{
  struct Pwm * self = (struct Pwm *)base;
  TCCR0A = 0;
  clear_bit(&PORTD, self->output_pin);
}
