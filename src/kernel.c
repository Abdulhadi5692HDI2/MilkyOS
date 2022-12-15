#include <stdint.h>
#include <stddef.h>
#include "limine.h"
#include "idt.h"

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

void init() {
	idt_init();
	struct limine_terminal *terminal = terminal_request.response->terminals[0];
	terminal_request.response->write(terminal, "[INFO] IDT Loaded successfully\n", 11);
	
}
// The following will be our kernel's entry point.
void _start(void) {
	// Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
	}
    init();
	struct limine_terminal *terminal = terminal_request.response->terminals[0];
	//terminal_request.response->write(terminal, "kernel: Hello World!", 11);
    done();
}
