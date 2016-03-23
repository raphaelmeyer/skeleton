#ifndef DEVICE_H
#define DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "device/timer.h"

struct IPwm;
struct Gpio;

enum DeviceState {
  Device_Idle,
  Device_Ringing
};

struct Device
{
  struct IPwm * bell;
  struct Timer bell_timer;
  struct Gpio * button;
  struct Gpio * notify;
  struct Timer notify_timer;

  enum DeviceState state;
};

void Device_init(
  struct Device * self, struct IPwm * bell, struct Gpio * button, struct Gpio * notify);

void Device_loop(struct Device *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //DEVICE_H
