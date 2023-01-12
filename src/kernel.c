#include <stdint.h>
#include <stddef.h>
#include "libc/libc.h"
#include "kernel.h"
#include "drivers/test/test.h"
#include "drivers/IO/osio.h"
#include "boot/limine.h"
#include "idt/idt.h"
#include "mem/mm/mm.h"
#include "mem/kheap/kheap.h"
#include "panic.h"
#include "hardware/pic/pic.h"
#include "hardware/pit/pit.h"
#include "drivers/keyboard/keyboard.h"
#include "tty.h"
#include "bootinfo.h"
#include "vfs/tmpfs/tmpfs.h"

char* currentfs = "tmpfs";
// kernel done function
static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}
void init_root() {
	struct folder root;
	root.path = OS_ROOT;
	root.ismount = true;
	changedir(root);
}
// initalize function
void init() {
	idt_init();
	init_dynamic_mem();
	testInit(); // the test driver. (smallest driver possible in MilkyOS)
	scrprint("fs: Using filesystem ");
	scrprint(currentfs);
	scrprint("\n");
	init_root();
	scrprint("\n");
	
}

// Main Kernel
void _start(void) {
	// call the init function
	init();
	// just print some stuff
	scrprint("Welcome to MilkyOS!");
	scrprint("\nKernel Version: 1.06-dev");
	scrprint("\n");

	for(;;) {keyboardCallback();}

	scrprint(">");
	// kernel is probally done now
	done();
	
}