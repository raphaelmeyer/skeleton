#include "device/gpio.h"
#include "device/io.h"

#include <avr/io.h>

void Gpio_init(struct Gpio * self, enum Port port, uint8_t pin)
{
  if (port == Port_B) {
    self->port = &PINB;
    self->ddr = &DDRB;
  } else if (port == Port_C) {
    self->port = &PINC;
    self->ddr = &DDRC;
  } else if (port == Port_D) {
    self->port = &PIND;
    self->ddr = &DDRD;
  }

  self->pin = pin;
}

void Gpio_set_direction(struct Gpio * self, enum Direction direction)
{
  self->direction = direction;
  if(Direction_Output == direction) {
    *self->ddr |= (1 << self->pin);
  }
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
