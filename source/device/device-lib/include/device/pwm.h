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

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_PWM_H
