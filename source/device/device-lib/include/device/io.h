#ifndef SKELETON_IO_H
#define SKELETON_IO_H

#include <stdint.h>

static inline uint8_t bit(uint8_t bit)
{
  return (1 << bit);
}

static inline uint8_t set_bit(uint8_t volatile * port, uint8_t bit)
{
  *port |= (1 << bit);
}

#endif //SKELETON_IO_H
