#include <avr/io.h>

// -----------------------------------------------------------------------------
// GPIO
// -----------------------------------------------------------------------------

uint8_t volatile PINB = 0;
uint8_t volatile PORTB = 0;
uint8_t volatile DDRB = 0;

uint8_t const PINB0 = 0;
uint8_t const PINB1 = 1;
uint8_t const PINB2 = 2;
uint8_t const PINB3 = 3;
uint8_t const PINB4 = 4;
uint8_t const PINB5 = 5;
uint8_t const PINB6 = 6;
uint8_t const PINB7 = 7;

uint8_t const PORTB0 = 0;
uint8_t const PORTB1 = 1;
uint8_t const PORTB2 = 2;
uint8_t const PORTB3 = 3;
uint8_t const PORTB4 = 4;
uint8_t const PORTB5 = 5;
uint8_t const PORTB6 = 6;
uint8_t const PORTB7 = 7;

uint8_t const DDB0 = 0;
uint8_t const DDB1 = 1;
uint8_t const DDB2 = 2;
uint8_t const DDB3 = 3;
uint8_t const DDB4 = 4;
uint8_t const DDB5 = 5;
uint8_t const DDB6 = 6;
uint8_t const DDB7 = 7;

uint8_t volatile PINC = 0;
uint8_t volatile PORTC = 0;
uint8_t volatile DDRC = 0;

uint8_t const PINC0 = 0;
uint8_t const PINC1 = 1;
uint8_t const PINC2 = 2;
uint8_t const PINC3 = 3;
uint8_t const PINC4 = 4;
uint8_t const PINC5 = 5;
uint8_t const PINC6 = 6;
uint8_t const PINC7 = 7;

uint8_t const PORTC0 = 0;
uint8_t const PORTC1 = 1;
uint8_t const PORTC2 = 2;
uint8_t const PORTC3 = 3;
uint8_t const PORTC4 = 4;
uint8_t const PORTC5 = 5;
uint8_t const PORTC6 = 6;
uint8_t const PORTC7 = 7;

uint8_t const DDC0 = 0;
uint8_t const DDC1 = 1;
uint8_t const DDC2 = 2;
uint8_t const DDC3 = 3;
uint8_t const DDC4 = 4;
uint8_t const DDC5 = 5;
uint8_t const DDC6 = 6;
uint8_t const DDC7 = 7;

uint8_t volatile PIND = 0;
uint8_t volatile PORTD = 0;
uint8_t volatile DDRD = 0;

uint8_t const PIND0 = 0;
uint8_t const PIND1 = 1;
uint8_t const PIND2 = 2;
uint8_t const PIND3 = 3;
uint8_t const PIND4 = 4;
uint8_t const PIND5 = 5;
uint8_t const PIND6 = 6;
uint8_t const PIND7 = 7;

uint8_t const PORTD0 = 0;
uint8_t const PORTD1 = 1;
uint8_t const PORTD2 = 2;
uint8_t const PORTD3 = 3;
uint8_t const PORTD4 = 4;
uint8_t const PORTD5 = 5;
uint8_t const PORTD6 = 6;
uint8_t const PORTD7 = 7;

uint8_t const DDD0 = 0;
uint8_t const DDD1 = 1;
uint8_t const DDD2 = 2;
uint8_t const DDD3 = 3;
uint8_t const DDD4 = 4;
uint8_t const DDD5 = 5;
uint8_t const DDD6 = 6;
uint8_t const DDD7 = 7;

// -----------------------------------------------------------------------------
// Timer 0
// -----------------------------------------------------------------------------

uint8_t volatile TCCR0A = 0;

uint8_t const WGM00 = 0;
uint8_t const WGM01 = 1;
uint8_t const COM0B0 = 4;
uint8_t const COM0B1 = 5;
uint8_t const COM0A0 = 6;
uint8_t const COM0A1 = 7;

uint8_t volatile TCCR0B = 0;

uint8_t const CS00 = 0;
uint8_t const CS01 = 1;
uint8_t const CS02 = 2;
uint8_t const WGM02 = 3;
uint8_t const FOC0B = 6;
uint8_t const FOC0A = 7;

uint8_t volatile OCR0A = 0;

// -----------------------------------------------------------------------------
// Timer 1
// -----------------------------------------------------------------------------

uint8_t volatile TCCR1A = 0;

uint8_t const WGM10 = 0;
uint8_t const WGM11 = 1;
uint8_t const COM1B0 = 4;
uint8_t const COM1B1 = 5;
uint8_t const COM1A0 = 6;
uint8_t const COM1A1 = 7;

uint8_t volatile TCCR1B = 0;

uint8_t const CS10 = 0;
uint8_t const CS11 = 1;
uint8_t const CS12 = 2;
uint8_t const WGM12 = 3;
uint8_t const WGM13 = 4;
uint8_t const ICES1 = 6;
uint8_t const ICNC1 = 7;

uint16_t volatile OCR1A = 0;

uint8_t volatile TIMSK1 = 0;

uint8_t const TOIE1 = 0;
uint8_t const OCIE1A = 1;
uint8_t const OCIE1B = 2;
uint8_t const ICIE1 = 5;
