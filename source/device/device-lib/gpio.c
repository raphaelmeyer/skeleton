#include "device/gpio.h"
#include "device/io.h"

#include <avr/io.h>

void Gpio_init(struct Gpio * self, enum Port port, uint8_t pin)
{
  if (port == Port_B) {
    self->port = &PINB;
  } else if (port == Port_C) {
    self->port = &PINC;
  } else if (port == Port_D) {
    self->port = &PIND;
  }

  self->pin = pin;
}

void Gpio_set_direction(struct Gpio * self, enum Direction direction)
{
  self->direction = direction;
}

enum Signal Gpio_get_signal(struct Gpio * self)
{
  enum Signal signal = Signal_Undefined;
  if(self->direction == Direction_Input) {
    if(*(self->port) & bit(self->pin)) {
      signal = Signal_High;
    } else {
      signal = Signal_Low;
    }
  }
  return signal;
}
