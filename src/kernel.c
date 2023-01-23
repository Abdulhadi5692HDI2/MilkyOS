#include <stdint.h>
#include <stddef.h>
#include "libc/libc.h"
#include "gdt/gdt.h"
#include "kernel.h"
#include "drivers/test/test.h"
#include "drivers/IO/osio.h"
#include "boot/limine.h"
#include "mem/mm/mm.h"
#include "mem/kheap/kheap.h"
#include "panic.h"
#include "bootinfo.h"
#include "vfs/tmpfs/tmpfs.h"

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
	gdt_init();
	init_dynamic_mem();
	testInit(); // the test driver. (smallest driver possible in MilkyOS)
	init_root();	
}

// Main Kernel
void _start(void) {
	// call the init function
	init();
	// just print some stuff
	printf("\nWelcome to MilkyOS!");
	printf("\nKernel Version: 1.09-dev");
	printf("\n");
	// kernel is probally done now
	done();
	
}