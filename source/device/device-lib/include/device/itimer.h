#ifndef SKELETON_ITIMER_H
#define SKELETON_ITIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct ITimer
{
  void (* start)(struct ITimer * base, uint32_t milliseconds);
  void (* stop)(struct ITimer * base);
  bool (* expired)(struct ITimer * base);
};

void Timer_start(struct ITimer * base, uint32_t milliseconds);
bool Timer_expired(struct ITimer * base);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_ITIMER_H
