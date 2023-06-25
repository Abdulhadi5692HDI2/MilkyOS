#include <cpu/idt/idt.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    asm volatile ("cli; hlt");
}
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x28; 
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint64_t)isr >> 32;
    descriptor->reserved       = 0;
}

extern void* isr_stub_table[];

void enableint();
void disableint();

void idt_init(void);
void idt_init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        bool vectors[32];
        vectors[vector] = true;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    enableint();
}

void enableint() {
    __asm__ volatile ("sti");
}

void disableint() {
    __asm__ volatile ("cli");
}