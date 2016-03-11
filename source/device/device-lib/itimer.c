#include "device/itimer.h"

void Timer_start(struct ITimer * base) {
  return base->start(base);
}

bool Timer_expired(struct ITimer * base) {
  return base->expired(base);
}
