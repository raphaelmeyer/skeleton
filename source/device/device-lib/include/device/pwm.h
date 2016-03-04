#ifndef SKELETON_PWM_H
#define SKELETON_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct IPwm
{
  void (* on)(struct IPwm * base);
  void (* off)(struct IPwm * base);
};

struct Pwm
{
  struct IPwm interface;
};

void Pwm_on(struct IPwm *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_PWM_H
