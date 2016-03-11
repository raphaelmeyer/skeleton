#ifndef SKELETON_ITIMER_H
#define SKELETON_ITIMER_H

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
bool Timer_expired(struct ITimer *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_ITIMER_H
