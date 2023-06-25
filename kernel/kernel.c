#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <memfunc.h>
#include <cpu/gdt/gdt.h>

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
    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }
    gdt_init();
    idt_init();
}

void _start(void) {
    init();

    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    for (size_t i = 0; i < 100; i++) {
        uint32_t *fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0x2cfa02;
    }

    // We're done, just hang...
    hcf();
}
