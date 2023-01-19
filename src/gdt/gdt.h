#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


void gdt_init(void);
void gdt_reload();
#endif
