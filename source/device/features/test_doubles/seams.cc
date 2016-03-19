#include <avr/io.h>

uint8_t volatile PINB;
uint8_t volatile PORTB;
uint8_t volatile DDRB;

uint8_t volatile PINC;
uint8_t volatile PORTC;
uint8_t volatile DDRC;

uint8_t volatile PIND;
uint8_t volatile PORTD;
uint8_t volatile DDRD;

uint8_t volatile TCCR1A;
uint8_t volatile TCCR1B;
uint16_t volatile OCR1A;

uint8_t const CS10 = 0;
uint8_t const WGM12 = 3;
