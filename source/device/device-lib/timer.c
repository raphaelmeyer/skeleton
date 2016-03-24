#include "device/timer.h"

#include "device/system_tick.h"

static void update(void * argument) {
  struct Timer * self = (struct Timer *)argument;
  if(self->remaining > 0) {
    --self->remaining;
    if(self->remaining == 0) {
      self->expired = true;
    }
  }
}

void Timer_init(struct Timer * self) {
  self->expired = false;
  self->remaining = 0;

  SystemTick_register(update, self);
}

void Timer_start(struct Timer * self, uint32_t milliseconds) {
  if (milliseconds == 0) {
    self->expired = true;
  } else {
    self->expired = false;
    self->remaining = milliseconds;
  }
}

void Timer_stop(struct Timer * self) {
  self->remaining = 0;
  self->expired = false;
}

bool Timer_expired(struct Timer * self) {
  return self->expired;
}
