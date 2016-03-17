#include "device/system_tick.h"

#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect) {
}

void SystemTick_init() {

}

void SystemTick_register(void(* notify)(void *), void * observer) {

}
