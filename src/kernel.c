#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "drivers/test/test.h"
#include "drivers/IO/osio.h"
#include "boot/limine.h"
#include "misc/misc.h"
#include "idt/idt.h"
#include "mem/mm/mm.h"
#include "panic.h"
#include "hardware/pic.h"
#include "drivers/keyboard/keyboard.h"
#include "vfs/fs.h"
#include "tty.h"


// kernel done function
static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
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
	scrprint("test:");
	testInit(); // the test driver. (smallest driver possible in MilkyOS)
	scrprint("keyboard:");
	kernelInitKeyboard(); // the keyboard driver. (currently supports PS/2 keyboards)
	scrprint("[ OK ] Loaded drivers!\n");
	
}

// Main Kernel
void _start(void) {
	// call the init function
	init();
	// just print some stuff
	scrprint("Welcome to MilkyOS!");
	scrprint("\nKernel Version: 1.04-dev");
	scrprint("\n");
	// kernel is probally done now
	done();
	
}
