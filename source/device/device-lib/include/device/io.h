#ifndef SKELETON_IO_H
#define SKELETON_IO_H

#include <stdint.h>
#include <stdbool.h>

static inline uint8_t bit_value(uint8_t bit) {
  return (1 << bit);
}

static inline bool is_bit_set(uint8_t volatile * port, uint8_t bit) {
  return (0 != ((*port) & bit_value(bit)));
}

static inline void set_bit(uint8_t volatile * port, uint8_t bit) {
  *port |= bit_value(bit);
}

static inline void clear_bit(uint8_t volatile * port, uint8_t bit) {
  *port &= ~bit_value(bit);
}

#endif //SKELETON_IO_H
