#include "device/pwm.h"

#include "device/io.h"

#include <avr/io.h>

static uint8_t const Prescaler_256 = 0x04;
static uint8_t const Mode_Toggle = 0x40;
static uint8_t const FastPwmToggle_RegA = 0x03;
static uint8_t const FastPwmToggle_RegB = 0x08;

void on(struct IPwm * base);
void off(struct IPwm * base);

void Pwm_init(struct Pwm * self)
{
  self->interface.on = on;
  self->interface.off = off;
  set_bit(&DDRD, 6);
}

void on(struct IPwm * base)
{
  uint8_t const Compare_440_Hz = 70;

  TCCR0A = Mode_Toggle | FastPwmToggle_RegA;
  TCCR0B = FastPwmToggle_RegB | Prescaler_256;
  OCR0A = Compare_440_Hz;
}

void off(struct IPwm * base)
{
  TCCR0A = 0;
}
