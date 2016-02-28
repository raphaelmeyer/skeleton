#include "device/gpio.h"

#include <avr/io.h>

void Gpio_init(struct Gpio * self)
{

}

void Gpio_set_direction(struct IGpio * base, enum Direction direction)
{

}

enum Signal Gpio_get_signal(struct IGpio * base)
{
  if (PORTB) {
    return Signal_High;
  }
  return Signal_Low;
}
