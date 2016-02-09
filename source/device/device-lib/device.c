#include "device/device.h"

#include <avr/io.h>
#include <util/delay.h>

void Device_init()
{
  DDRB |= _BV(DDB5);
}

void Device_loop()
{
  PORTB |= _BV(PORTB5);
  _delay_ms(500);

  PORTB &= ~_BV(PORTB5);
  _delay_ms(500);
}
