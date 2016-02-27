#ifndef SKELETON_GPIO_H
#define SKELETON_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

struct IGpio
{
  void (*foo)();
};

struct Gpio
{
  struct IGpio interface;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_GPIO_H
