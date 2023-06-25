#ifndef _IDT_H
#define _IDT_H

#define IDT_MAX_DESCRIPTORS 256
#include <stdint.h>

typedef struct {
    uint16_t    isr_low;
    uint16_t    kernel_cs;
    uint32_t    reserved;
    uint8_t     attributes;
    uint32_t    isr_high;
} __attribute__((packed)) idt_entry_t;


__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

void idt_init(void);
#endif