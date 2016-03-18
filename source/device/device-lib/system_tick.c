#include "device/system_tick.h"

#include <device/io.h>

#include <avr/interrupt.h>
#include <avr/io.h>

struct Observer {
  void(* notify)(void *);
  void * observer;
};

static struct Observer _observers[2];
static uint8_t _observers_registered = 0;

ISR(TIMER1_COMPA_vect) {
  uint8_t i;
  for(i = 0; i < _observers_registered; ++i) {
    _observers[i].notify(_observers[i].observer);
  }
}

void SystemTick_init() {
  TCCR1A = 0;
  TCCR1B = bit_value(WGM12) | bit_value(CS10);
  OCR1A = 7999;

  _observers_registered = 0;
}

void SystemTick_register(void(* notify)(void *), void * observer) {
  _observers[_observers_registered].notify = notify;
  _observers[_observers_registered].observer = observer;
  ++_observers_registered;
}
