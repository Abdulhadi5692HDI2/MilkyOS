#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <memfunc.h>
#include <cpu/gdt/gdt.h>
#include <mem/pmem/pmem.h>
// replace: #include <term/term.h>
#include "../lib/flanterm/flanterm.h"
#include "../lib/flanterm/backends/fb.h"


static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};



// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}


static void init() {
	//term_init();
	
    gdt_init();
    idt_init();
}

void _start(void) {
    init();
	struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
	uint32_t *fb_ptr                       = framebuffer->address;
	uint64_t *fb_width                     = framebuffer->width;
	uint64_t *fb_height                    = framebuffer->height;
	uint64_t *fb_pitch                     = framebuffer->pitch;
	struct flanterm_context *ft_ctx = flanterm_fb_simple_init(
		fb_ptr, fb_width, fb_height, fb_pitch
	);
	const char msg[] = "Hello world\n";

	flanterm_write(ft_ctx, msg, sizeof(msg));
    
    // We're done, just hang...
    hcf();
}
