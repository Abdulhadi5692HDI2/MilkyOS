#ifndef _PMEM_H
#define _PMEM_H

#include <stdint.h>
#include <stddef.h>

void *malloc(size_t size);
void free(void *p);
#endif