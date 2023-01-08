#include "kheap.h"
#include <stdint.h>

uint32_t kmalloc(uint32_t sz) {
  uint32_t placement_address = 0;
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
}