#include "device/timer.h"

static void start(struct ITimer * base, uint32_t milliseconds);
static bool expired(struct ITimer * base);
static void update(struct ITimer * base);

void Timer_init(struct Timer * self) {
  self->interface.start = start;
  self->interface.expired = expired;
  self->interface.update = update;

  self->expired = false;
}

static void start(struct ITimer * base, uint32_t milliseconds) {
  struct Timer * self = (struct Timer *)base;
  if (milliseconds == 0) {
    self->expired = true;
  }
}

static bool expired(struct ITimer * base) {
  struct Timer * self = (struct Timer *)base;
  return self->expired;
}

static void update(struct ITimer * base)  {
}

