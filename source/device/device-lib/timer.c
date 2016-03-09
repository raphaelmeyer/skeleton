#include "device/timer.h"

void Timer_start(struct ITimer * base) {
  return base->start(base);
}
