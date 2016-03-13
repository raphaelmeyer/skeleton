#include "device/pwm.h"

#include "device/io.h"

#include <avr/io.h>

void Pwm_init(struct Pwm * self)
{
  set_bit(&DDRD, 6);
}
