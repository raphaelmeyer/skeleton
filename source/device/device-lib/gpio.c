#include "device/gpio.h"

#include <avr/io.h>

void Gpio_init(struct Gpio * self)
{

}

void Gpio_set_direction(struct IGpio * base, enum Direction direction)
{
  struct Gpio * self =(struct Gpio *)base;
  self->direction = direction;
}

enum Signal Gpio_get_signal(struct IGpio * base)
{
  enum Signal signal = Signal_Undefined;
  struct Gpio * self =(struct Gpio *)base;
  if(self->direction == Direction_Input) {
    if(PORTB) {
      signal = Signal_High;
    } else {
      signal = Signal_Low;
    }
  }
  return signal;
}
