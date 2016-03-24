#ifndef SKELETON_IPWM_H
#define SKELETON_IPWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct IPwm
{
  void (* on)(struct IPwm *);
  void (* off)(struct IPwm *);
};

void Pwm_on(struct IPwm *);
void Pwm_off(struct IPwm *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_IPWM_H
