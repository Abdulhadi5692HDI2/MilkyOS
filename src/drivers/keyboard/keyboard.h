#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#define _DRIVER1 "keyboard"

#include <stddef.h>
#include <stdint.h>

void chkscancode(uint8_t scancode1);
void keyboardCallback();
void kernelInitKeyboard();
void initKeyboard();
#endif