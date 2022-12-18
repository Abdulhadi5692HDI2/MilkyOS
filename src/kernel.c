#include <stdint.h>
#include <stddef.h>
#include "drivers/test/test.h"
#include "boot/limine.h"
#include "misc/misc.h"
#include "idt/idt.h"
#include "mem/paging/paging.h"
#include "panic.h"
#include "hardware/pic.h"

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
	testInit(); // the test driver. (smallest driver possible in MilkyOS)
	scrprint("[ OK ] Loaded drivers!\n");
	PIC_remap(0x20, 0x28);
	scrprint("[ OK ] Configured and remapped the PIC.\n");
	scrprint("[ PENDING ] Starting main kernel!\n");
	
}



#define VER "1.00-dev"
#define NAME "MilkyOS"
// The following will be our kernel's entry point.
void _start(void) {
	init();
	
	scrprint(NAME);
	scrprint("\n");
	scrprint("The version your running is: ");
	scrprint(VER);
	//panic("A unknown error has happened.", "kernel");
	done();
}
