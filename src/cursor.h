#ifndef _CURSOR_H
#define _CURSOR_H
#include "kernel.h"

// cursor functions
void cursor_forward() {
	scrprint(" ");
}
void cursor_backward() {
	scrprint("\b");
}
#endif