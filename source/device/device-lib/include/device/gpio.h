#ifndef SKELETON_GPIO_H
#define SKELETON_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

enum Signal
{
  Signal_Undefined,
  Signal_Low,
  Signal_High
};

struct IGpio
{
  enum Signal (*get_signal)(struct IGpio *);
};

struct Gpio
{
  struct IGpio interface;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_GPIO_H
