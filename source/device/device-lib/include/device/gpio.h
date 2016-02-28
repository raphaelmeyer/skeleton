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

enum Direction
{
  Direction_Undefined,
  Direction_Input,
  Direction_Output
};

struct IGpio
{
  enum Signal (*get_signal)(struct IGpio *);
};

struct Gpio
{
  struct IGpio interface;
  enum Direction direction;
};

void Gpio_init(struct Gpio *);
void Gpio_set_direction(struct IGpio *, enum Direction);
enum Signal Gpio_get_signal(struct IGpio *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_GPIO_H
