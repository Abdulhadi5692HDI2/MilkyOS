#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
	uint16_t	isr_low;
	uint16_t	kernel_cs;
	uint8_t		reserved;
	uint8_t		attributes;
	uint32_t	isr_high;
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

void exception_handler(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);