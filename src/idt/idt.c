#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "../drivers/IO/osio.h"
#include "../hardware/pic/pic.h"
#include "../panic.h"
#include "idt.h"

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    panic2("A exception has happened!", "idt");
	__asm__ volatile ("cli; hlt");
}

extern void* isr_stub_table[];
extern void* irq0;
extern void* irq1;
extern void* irq2;
extern void* irq3;
extern void* irq4;
extern void* irq5;
extern void* irq6;
extern void* irq7;
extern void* irq8;
extern void* irq9;
extern void* irq10;
extern void* irq11;
extern void* irq12;
extern void* irq13;
extern void* irq14;
extern void* irq15;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	idt_entry_t* descriptor = &idt[vector];
	
	descriptor->isr_low		= (uint32_t)isr & 0xFFFF;
	descriptor->kernel_cs	= 0x08;
	descriptor->attributes	= flags;
	descriptor->isr_high	= (uint32_t)isr >> 16;
	descriptor->reserved	= 0;
}
void irq_handler() {
    outb(0x20, 0x20);
}

void idt_init(void);
void idt_init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;
    PIC_remap(0x20, 0x28);

    // ISRS
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    // irqs
    idt_set_descriptor((int)32, irq0, 0x8E);
    idt_set_descriptor((int)33, irq1, 0x8E);
    idt_set_descriptor((int)34, irq2, 0x8E);
    idt_set_descriptor((int)35, irq3, 0x8E);
    idt_set_descriptor((int)36, irq4, 0x8E);
    idt_set_descriptor((int)37, irq5, 0x8E);
    idt_set_descriptor((int)38, irq6, 0x8E);
    idt_set_descriptor((int)39, irq7, 0x8E);
    idt_set_descriptor((int)40, irq8, 0x8E);
    idt_set_descriptor((int)41, irq9, 0x8E);
    idt_set_descriptor((int)42, irq10, 0x8E);
    idt_set_descriptor((int)43, irq11, 0x8E);
    idt_set_descriptor((int)44, irq12, 0x8E);
    idt_set_descriptor((int)45, irq13, 0x8E);
    idt_set_descriptor((int)46, irq14, 0x8E);
    idt_set_descriptor((int)47, irq15, 0x8E);
 
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}