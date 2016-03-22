#ifndef DEVICE_H
#define DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

struct IPwm;
struct Gpio;
struct Timer;

enum DeviceState {
  Device_Idle,
  Device_Ringing
};

struct Device
{
  struct IPwm * bell;
  struct Gpio * button;
  struct Timer * timer;
  struct Gpio * notify;

  enum DeviceState state;
};

void Device_init(
  struct Device * self, struct IPwm * bell, struct Gpio * button, struct Timer * timer,
  struct Gpio * notify);

void Device_loop(struct Device *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //DEVICE_H
