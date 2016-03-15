#include "device/timer.h"

static bool expired(struct ITimer * base);
static void update(struct ITimer * base);

void Timer_init(struct Timer * self) {
  self->interface.expired = expired;
}

static bool expired(struct ITimer * base) {
  return false;
}

static void update(struct ITimer * base)  {
}

