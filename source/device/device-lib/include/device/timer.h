#ifndef SKELETON_TIMER_H
#define SKELETON_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "device/itimer.h"

struct Timer
{
  struct ITimer interface;
};


void Timer_init(struct Timer * self);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_TIMER_H
