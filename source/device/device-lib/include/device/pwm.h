#ifndef SKELETON_PWM_H
#define SKELETON_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "device/ipwm.h"

struct Pwm
{
  struct IPwm interface;
};

void Pwm_init(struct Pwm * self);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_PWM_H
