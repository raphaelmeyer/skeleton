#ifndef DEVICE_H
#define DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

struct Pwm;
struct Gpio;

struct Device {};

void Device_init(struct Device * self, struct Pwm * bell, struct Gpio * button);
void Device_start(struct Device * self);
void Device_stop(struct Device * self);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //DEVICE_H
