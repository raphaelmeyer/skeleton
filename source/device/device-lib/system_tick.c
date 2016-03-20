#include "device/system_tick.h"

#include <device/io.h>

#include <avr/interrupt.h>
#include <avr/io.h>

struct Observer {
  void(* notify)(void *);
  void * observer;
};

static uint8_t const MaxObservers = 2;

struct SystemTick {
  struct Observer observers[2];
  uint8_t observers_registered;
};

static struct SystemTick system_tick;

ISR(TIMER1_COMPA_vect) {
  uint8_t i;
  for(i = 0; i < system_tick.observers_registered; ++i) {
    void * observer = system_tick.observers[i].observer;
    system_tick.observers[i].notify(observer);
  }
}

void SystemTick_init() {
  system_tick.observers_registered = 0;

  TCCR1A = 0;
  TCCR1B = bit_value(WGM12) | bit_value(CS10);
  OCR1A = 7999;
  TIMSK1 = bit_value(OCIE1A);
}

void SystemTick_register(void(* notify)(void *), void * observer) {
  uint8_t next = system_tick.observers_registered;
  if(next < MaxObservers) {
    system_tick.observers[next].notify = notify;
    system_tick.observers[next].observer = observer;
    ++system_tick.observers_registered;
  }
}
