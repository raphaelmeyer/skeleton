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

uint8_t const Pin_0 = 0;
uint8_t const Pin_3 = 3;

struct IGpio
{
  enum Signal (*get_signal)(struct IGpio *);
};

struct Gpio
{
  struct IGpio interface;
  enum Direction direction;
  uint8_t volatile * port;
  uint8_t pin;
};

void Gpio_init(struct Gpio *, enum Port port, uint8_t pin);
void Gpio_set_direction(struct IGpio *, enum Direction);
enum Signal Gpio_get_signal(struct IGpio *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_GPIO_H
