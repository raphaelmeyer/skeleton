//
// Created by raphael on 09/02/16.
//

#ifndef SKELETON_IO_H
#define SKELETON_IO_H

#include <stdint.h>

extern uint8_t _BV(uint8_t bit);

extern uint8_t PINB;
extern uint8_t PORTB;
extern uint8_t DDRB;

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


#endif //SKELETON_IO_H
