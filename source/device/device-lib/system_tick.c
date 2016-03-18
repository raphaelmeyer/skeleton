#include "device/system_tick.h"

#include <device/io.h>

#include <avr/interrupt.h>
#include <avr/io.h>

struct Observer {
  void(* notify)(void *);
  void * observer;
};

static struct Observer _observer;

ISR(TIMER1_COMPA_vect) {
  _observer.notify(_observer.observer);
}

void SystemTick_init() {
  TCCR1A = 0;
  TCCR1B = bit_value(WGM12) | bit_value(CS10);
  OCR1A = 7999;
}

void SystemTick_register(void(* notify)(void *), void * observer) {
  _observer.notify = notify;
  _observer.observer = observer;
}
