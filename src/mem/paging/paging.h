#ifndef _PAGING_H
#define _PAGING_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();
void setPaging();
#endif