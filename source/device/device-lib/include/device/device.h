#ifndef DEVICE_H
#define DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

struct IPwm;
struct Gpio;
struct ITimer;

struct Device
{
  struct IPwm * bell;
  struct Gpio * button;
};

void Device_init(struct Device * self, struct IPwm * bell,
                 struct Gpio * button, struct ITimer * timer);
void Device_loop(struct Device *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //DEVICE_H
