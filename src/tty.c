#include <stdint.h>
#include <stddef.h>
#include "boot/limine.h"
// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};


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
	struct limine_terminal *terminal = terminal_request.response->terminals[0];
	terminal_request.response->write(terminal, "", ((uint64_t)(-4)));
}

