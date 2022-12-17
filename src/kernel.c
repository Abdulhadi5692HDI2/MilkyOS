#include <stdint.h>
#include <stddef.h>
#include "drivers/test.h"
#include "limine.h"
#include "misc/misc.h"
#include "idt/idt.h"
#include "mem/paging/paging.h"

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

//extern void newline();

void scrprint(const char *msg, ...) {
	struct limine_terminal *terminal = terminal_request.response->terminals[0];
	if (msg == '\n') {
		terminal->rows++;
		terminal_request.response->write(terminal, msg, strlen(msg)); // libc-less strlen implementation in strlen.c
		terminal->columns = 0;
	} else {
		terminal_request.response->write(terminal, msg, strlen(msg)); // libc-less strlen implementation in strlen.c
	}
}

void init() {
	// Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
	}
	scrprint("[ OK ] Loaded string functions from misc.h!\n");
	idt_init();
	scrprint("[ OK ] IDT Loaded!\n");
	//setPaging();
	//scrprint("[ OK ] Enabled Paging!\n");
	scrprint("[ ERROR ] Could not enable Paging! System starting without paging!\n");
	testInit();
	scrprint("[ OK ] Loaded drivers!\n");
	scrprint("[ PENDING ] Starting main kernel!\n");
	
}

// The following will be our kernel's entry point.
void _start(void) {
	init();
    scrprint("MilkyOS version 1.0");
	done();
}
