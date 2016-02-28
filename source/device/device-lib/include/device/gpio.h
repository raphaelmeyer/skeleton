#ifndef SKELETON_GPIO_H
#define SKELETON_GPIO_H

#include <stdint.h>

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

enum Port
{
  Port_B
};

enum Pin
{
  Pin_0,
  Pin_1,
  Pin_2,
  Pin_3,
  Pin_4,
  Pin_5,
  Pin_6,
  Pin_7,
};

struct IGpio
{
  enum Signal (*get_signal)(struct IGpio *);
};

struct Gpio
{
  struct IGpio interface;
  enum Direction direction;
  uint8_t volatile * port;
};

void Gpio_init(struct Gpio *, enum Port port, enum Pin pin);
void Gpio_set_direction(struct IGpio *, enum Direction);
enum Signal Gpio_get_signal(struct IGpio *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_GPIO_H
