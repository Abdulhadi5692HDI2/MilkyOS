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
	scrprint("[ OK ] IDT Loaded!\n");
	init_dynamic_mem();
	scrprint("[ OK ] Initialized Dynamic Memory Management\n");
	scrprint("test:");
	testInit(); // the test driver. (smallest driver possible in MilkyOS)
	scrprint("keyboard:");
	kernelInitKeyboard(); // the keyboard driver. (currently supports PS/2 keyboards)
	scrprint("[ OK ] Loaded drivers!\n");
	scrprint("fs: Using filesystem ");
	scrprint(currentfs);
	init_root();
	scrprint("\n");
	scrprint("\n");
	
}

// Main Kernel
void _start(void) {
	// call the init function
	init();
	// just print some stuff
	scrprint("Welcome to MilkyOS!");
	scrprint("\nKernel Version: 1.05-dev");
	scrprint("\n");
	printinfo();
	scrprint("\n");
	scrprint ("\n");
	// kernel is probally done now
	done();
	
}