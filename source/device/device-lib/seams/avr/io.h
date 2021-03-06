#ifndef SEAMS_AVR_IO_H
#define SEAMS_AVR_IO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// GPIO
// -----------------------------------------------------------------------------

extern uint8_t volatile PINB;
extern uint8_t volatile PORTB;
extern uint8_t volatile DDRB;

extern uint8_t const PINB0;
extern uint8_t const PINB1;
extern uint8_t const PINB2;
extern uint8_t const PINB3;
extern uint8_t const PINB4;
extern uint8_t const PINB5;
extern uint8_t const PINB6;
extern uint8_t const PINB7;

extern uint8_t const PORTB0;
extern uint8_t const PORTB1;
extern uint8_t const PORTB2;
extern uint8_t const PORTB3;
extern uint8_t const PORTB4;
extern uint8_t const PORTB5;
extern uint8_t const PORTB6;
extern uint8_t const PORTB7;

extern uint8_t const DDB0;
extern uint8_t const DDB1;
extern uint8_t const DDB2;
extern uint8_t const DDB3;
extern uint8_t const DDB4;
extern uint8_t const DDB5;
extern uint8_t const DDB6;
extern uint8_t const DDB7;

extern uint8_t volatile PINC;
extern uint8_t volatile PORTC;
extern uint8_t volatile DDRC;

extern uint8_t const PINC0;
extern uint8_t const PINC1;
extern uint8_t const PINC2;
extern uint8_t const PINC3;
extern uint8_t const PINC4;
extern uint8_t const PINC5;
extern uint8_t const PINC6;
extern uint8_t const PINC7;

extern uint8_t const PORTC0;
extern uint8_t const PORTC1;
extern uint8_t const PORTC2;
extern uint8_t const PORTC3;
extern uint8_t const PORTC4;
extern uint8_t const PORTC5;
extern uint8_t const PORTC6;
extern uint8_t const PORTC7;

extern uint8_t const DDC0;
extern uint8_t const DDC1;
extern uint8_t const DDC2;
extern uint8_t const DDC3;
extern uint8_t const DDC4;
extern uint8_t const DDC5;
extern uint8_t const DDC6;
extern uint8_t const DDC7;

extern uint8_t volatile PIND;
extern uint8_t volatile PORTD;
extern uint8_t volatile DDRD;

extern uint8_t const PIND0;
extern uint8_t const PIND1;
extern uint8_t const PIND2;
extern uint8_t const PIND3;
extern uint8_t const PIND4;
extern uint8_t const PIND5;
extern uint8_t const PIND6;
extern uint8_t const PIND7;

extern uint8_t const PORTD0;
extern uint8_t const PORTD1;
extern uint8_t const PORTD2;
extern uint8_t const PORTD3;
extern uint8_t const PORTD4;
extern uint8_t const PORTD5;
extern uint8_t const PORTD6;
extern uint8_t const PORTD7;

extern uint8_t const DDD0;
extern uint8_t const DDD1;
extern uint8_t const DDD2;
extern uint8_t const DDD3;
extern uint8_t const DDD4;
extern uint8_t const DDD5;
extern uint8_t const DDD6;
extern uint8_t const DDD7;

// -----------------------------------------------------------------------------
// Timer 0
// -----------------------------------------------------------------------------

extern uint8_t volatile TCCR0A;

extern uint8_t const WGM00;
extern uint8_t const WGM01;
extern uint8_t const COM0B0;
extern uint8_t const COM0B1;
extern uint8_t const COM0A0;
extern uint8_t const COM0A1;

extern uint8_t volatile TCCR0B;

extern uint8_t const CS00;
extern uint8_t const CS01;
extern uint8_t const CS02;
extern uint8_t const WGM02;
extern uint8_t const FOC0B;
extern uint8_t const FOC0A;

extern uint8_t volatile OCR0A;

// -----------------------------------------------------------------------------
// Timer 1
// -----------------------------------------------------------------------------

extern uint8_t volatile TCCR1A;

extern uint8_t const WGM10;
extern uint8_t const WGM11;
extern uint8_t const COM1B0;
extern uint8_t const COM1B1;
extern uint8_t const COM1A0;
extern uint8_t const COM1A1;

extern uint8_t volatile TCCR1B;

extern uint8_t const CS10;
extern uint8_t const CS11;
extern uint8_t const CS12;
extern uint8_t const WGM12;
extern uint8_t const WGM13;
extern uint8_t const ICES1;
extern uint8_t const ICNC1;

extern uint16_t volatile OCR1A;

#define OCR1AL *((uint8_t *)(&OCR1A))
#define OCR1AH *((uint8_t *)(&OCR1A) + 1)

extern uint8_t volatile TIMSK1;

extern uint8_t const TOIE1;
extern uint8_t const OCIE1A;
extern uint8_t const OCIE1B;
extern uint8_t const ICIE1;

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SEAMS_AVR_IO_H
