#ifndef SKELETON_SEAMS_INTERRRUPT_H
#define SKELETON_SEAMS_INTERRRUPT_H

#include <avr/interrupt.h>

struct InterruptSpy {
  bool enabled;
};

extern InterruptSpy interrupt_spy;

#endif //SKELETON_SEAMS_INTERRRUPT_H
