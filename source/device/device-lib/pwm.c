#include "device/pwm.h"

#include <avr/io.h>

void Pwm_init(struct Pwm * self)
{
  DDRD |= (1 << 6);
}
