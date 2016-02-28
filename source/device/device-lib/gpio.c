#include "device/gpio.h"
#include "device/io.h"

#include <avr/io.h>

void Gpio_init(struct Gpio * self, enum Port port, uint8_t pin)
{
  self->port = &PINB;
  self->pin = pin;
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
    if(*(self->port) & bit(self->pin)) {
      signal = Signal_High;
    } else {
      signal = Signal_Low;
    }
  }
  return signal;
}
