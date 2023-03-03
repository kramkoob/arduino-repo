// Misc utils (le16)

#include "Arduino.h"
#include "utils.h"

// le16 had to be split, not sure two bytes could be returned... worth looking into
// return lower 8 bits ofa 16-bit integer
uint8_t le16b0(uint16_t val) {
  return val & 0xff;
}
// return upper 8 bits ofa 16-bit integer
uint8_t le16b1(uint16_t val) {
  return (val >> 8) & 0xff;
}
