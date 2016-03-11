#ifndef SKELETON_IPWM_H
#define SKELETON_IPWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct IPwm
{
  void (* on)(struct IPwm * base);
  void (* off)(struct IPwm * base);
};

void Pwm_on(struct IPwm *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_IPWM_H
