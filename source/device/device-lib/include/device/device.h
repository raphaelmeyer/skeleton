#ifndef DEVICE_H
#define DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

struct IPwm;
struct Gpio;

struct Device
{
};

void Device_init(struct Device * self, struct IPwm * bell, struct Gpio * button);
void Device_start(struct Device *);
void Device_stop(struct Device *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //DEVICE_H
