#include "device/itimer.h"

void Timer_start(struct ITimer * base) {
  return base->start(base);
}
