#include "device/gpio.h"
#include "device/io.h"

#include <avr/io.h>

uint8_t const Pin_0 = 0;
uint8_t const Pin_1 = 1;
uint8_t const Pin_2 = 2;
uint8_t const Pin_3 = 3;
uint8_t const Pin_4 = 4;
uint8_t const Pin_5 = 5;
uint8_t const Pin_6 = 6;
uint8_t const Pin_7 = 7;


void Gpio_init(struct Gpio * self, enum Port port, uint8_t pin)
{
  if (port == Port_B) {
    self->port = &PINB;
    self->ddr = &DDRB;
    self->output = &PORTB;
  } else if (port == Port_C) {
    self->port = &PINC;
    self->ddr = &DDRC;
    self->output = &PORTC;
  } else if (port == Port_D) {
    self->port = &PIND;
    self->ddr = &DDRD;
    self->output = &PORTD;
  }

  self->direction = Direction_Undefined;
  self->pin = pin;
}

void Gpio_set_direction(struct Gpio * self, enum Direction direction)
{
  self->direction = direction;
  if(Direction_Output == direction) {
    set_bit(self->ddr, self->pin);
    clear_bit(self->output, self->pin);
  } else if(Direction_Input == direction) {
    clear_bit(self->ddr, self->pin);
  }
}

enum Signal Gpio_get_signal(struct Gpio * self)
{
  enum Signal signal = Signal_Undefined;
  if(self->direction == Direction_Input) {
    if(is_bit_set(self->port, self->pin)) {
      signal = Signal_High;
    } else {
      signal = Signal_Low;
    }
  }
  return signal;
}

void Gpio_set_signal(struct Gpio * self, enum Signal signal)
{
  if(Direction_Output == self->direction) {
    if(signal == Signal_High) {
      set_bit(self->output, self->pin);
    } else if(signal == Signal_Low) {
      clear_bit(self->output, self->pin);
    }
  }
}
