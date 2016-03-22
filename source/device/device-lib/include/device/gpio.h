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
  Port_B,
  Port_C,
  Port_D
};

extern uint8_t const Pin_0;
extern uint8_t const Pin_1;
extern uint8_t const Pin_2;
extern uint8_t const Pin_3;
extern uint8_t const Pin_4;
extern uint8_t const Pin_5;
extern uint8_t const Pin_6;
extern uint8_t const Pin_7;

struct Gpio
{
  enum Direction direction;
  uint8_t volatile * port;
  uint8_t volatile * ddr;
  uint8_t volatile * output;
  uint8_t pin;
};

void Gpio_init(struct Gpio *, enum Port port, uint8_t pin);
void Gpio_set_direction(struct Gpio *, enum Direction);
enum Signal Gpio_get_signal(struct Gpio *);
void Gpio_set_signal(struct Gpio * self, enum Signal signal);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_GPIO_H
