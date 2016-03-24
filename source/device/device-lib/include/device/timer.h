#ifndef SKELETON_TIMER_H
#define SKELETON_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct Timer
{
  bool expired;
  uint32_t remaining;
};

void Timer_init(struct Timer * self);

void Timer_start(struct Timer * self, uint32_t milliseconds);
void Timer_stop(struct Timer * self);
bool Timer_expired(struct Timer * self);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_TIMER_H
