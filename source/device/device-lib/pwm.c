#include "device/pwm.h"

void Pwm_on(struct IPwm * base)
{
  base->on(base);
}
