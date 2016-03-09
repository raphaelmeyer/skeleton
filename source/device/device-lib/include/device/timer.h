#ifndef SKELETON_TIMER_H
#define SKELETON_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct ITimer
{
  void (* start)(struct ITimer *);
  void (* stop)(struct ITimer *);
  bool (* expired)(struct ITimer *);
};

void Timer_start(struct ITimer *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_TIMER_H
