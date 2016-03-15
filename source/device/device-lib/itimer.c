#include "device/itimer.h"

void Timer_start(struct ITimer * base, uint32_t milliseconds) {
  base->start(base, milliseconds);
}

bool Timer_expired(struct ITimer * base) {
  return base->expired(base);
}

void Timer_update(struct ITimer * base) {
  base->update(base);
}
