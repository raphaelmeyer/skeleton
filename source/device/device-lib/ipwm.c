#include "device/ipwm.h"

void Pwm_on(struct IPwm * base)
{
  base->on(base);
}
