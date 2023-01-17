#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "../tty.h"
#include "libc.h"


void printf(const char* format, ...) {
	va_list arg;
	va_start (arg, format);
	scrprint(format);
	va_end(arg);
}