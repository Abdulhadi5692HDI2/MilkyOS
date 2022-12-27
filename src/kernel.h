#ifndef _KERNEL_H
#define _KERNEL_H
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024
/*
	#define PS2_TEST_KEYBOARD
*/

void scrprint(const char *fmt, ...);
void scrclear();

#endif