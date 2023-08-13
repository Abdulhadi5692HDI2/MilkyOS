#include <stddef.h>
#include <stdint.h>
#include <limine.h>
#include <memfunc.h>
#include "../../lib/flanterm/flanterm.h"
#include "../../lib/flanterm/backends/fb.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


void term_init() {
	struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
	uint32_t *fb_ptr                       = framebuffer->address;
	uint64_t *fb_width                     = framebuffer->width;
	uint64_t *fb_height                    = framebuffer->height;
	uint64_t *fb_pitch                     = framebuffer->pitch;
	struct flanterm_context *ft_ctx = flanterm_fb_simple_init(
		fb_ptr, fb_width, fb_height, fb_pitch
	);
}