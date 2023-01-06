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

// a print (for hex) function
void scrprint_hex(uint32_t n) {
	int tmp;

    scrprint("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            scrprint (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            scrprint( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        scrprint (tmp-0xA+'a');
    }
    else
    {
        scrprint (tmp+'0');
    }
}

// a clean screen function
void scrclear() {
	struct limine_terminal *terminal = terminal_request.response->terminals[0];
	terminal_request.response->write(terminal, "", ((uint64_t)(-4)));
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
