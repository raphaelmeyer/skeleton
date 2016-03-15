#include "device/timer.h"

void Timer_init(struct Timer * self) {
  self->expired = false;
  self->remaining = 0;
}

void Timer_start(struct Timer * self, uint32_t milliseconds) {
  if (milliseconds == 0) {
    self->expired = true;
  } else {
    self->remaining = milliseconds;
  }
}

bool Timer_expired(struct Timer * self) {
  return self->expired;
}

void Timer_update(struct Timer * self)  {
  if(self->remaining > 0) {
    --self->remaining;
    if(self->remaining == 0) {
      self->expired = true;
    }
  }
}

