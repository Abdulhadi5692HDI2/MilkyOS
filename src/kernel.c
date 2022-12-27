#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "drivers/test/test.h"
#include "drivers/IO/osio.h"
#include "boot/limine.h"
#include "misc/misc.h"
#include "idt/idt.h"
#include "mem/paging/paging.h"
#include "mem/mm/mm.h"
#include "panic.h"
#include "hardware/pic.h"
#include "drivers/keyboard/keyboard.h"
#include "vfs/vfs.h"

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

// kernel done function
static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

// a print function
void scrprint(const char *fmt) {
	struct limine_terminal *terminal = terminal_request.response->terminals[0];
	if (fmt == '\n') {
		terminal->rows++;
		terminal_request.response->write(terminal, fmt, strlen(fmt)); // libc-less strlen implementation in strlen.c
		terminal->columns = 0;
	} else {
		terminal_request.response->write(terminal, fmt, strlen(fmt)); // libc-less strlen implementation in strlen.c
	}
	if (terminal->rows == SCREEN_WIDTH) {
		terminal->rows - 1;
		terminal->columns = 0;
	}
}

// a clean screen function
void scrclear() {
	scrprint("\033[2J");
	scrprint("\n");
}

// cursor functions
void cursor_forward() {
	scrprint(" ");
}
void cursor_backward() {
	scrprint("\b");
}

// initalize function
void init() {
	// Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
	}
	scrprint("[ OK ] Loaded string functions from misc.h!\n");
	idt_init();
	scrprint("[ OK ] IDT Loaded!\n");
	init_dynamic_mem();
	scrprint("[ OK ] Initialized Dynamic Memory Management\n");
	scrprint("test: ");
	testInit(); // the test driver. (smallest driver possible in MilkyOS)
	scrprint("keyboard: ");
	kernelInitKeyboard();
	scrprint("[ OK ] Loaded drivers!\n");
	init_vfs();
	scrprint("\n[ OK ] Initalized a virtual file system!\n");
	
}

// Main Kernel
void _start(void) {
	// call the init function
	init();

	// just print some stuff
	scrprint("Welcome to MilkyOS!");
	scrprint("\nKernel-Version: 1.02-dev");
	scrprint("\n");
	done();
	
}
