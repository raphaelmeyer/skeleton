#include "seams_interrupt.h"

InterruptSpy interrupt_spy;

void cli() {
  interrupt_spy.enabled = false;
}

void sei() {
  interrupt_spy.enabled = true;
}
