#ifndef SKELETON_PWM_H
#define SKELETON_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct IPwm
{
  void (* on)(struct IPwm * base, uint16_t frequency);
  void (* off)(struct IPwm * base);
};

struct Pwm
{
  struct IPwm interface;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_PWM_H
