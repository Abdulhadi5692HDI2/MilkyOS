#include "keyboard.h"
#include "../../tty.h"
#include "../IO/osio.h"
#include "../../libc/libc.h"
#include "../../cursor.h"

#define SC_MAX 57

static char key_buffer[256];

const char scancode_to_char[] = {
  '?', '?', '1', '2', '3', '4', '5',
  '6', '7', '8', '9', '0', '-', '=',
  '?', '?', 'Q', 'W', 'E', 'R', 'T',
  'Y', 'U', 'I', 'O', 'P', '[', ']',
  '?', '?', 'A', 'S', 'D', 'F', 'G',
  'H', 'J', 'K', 'L', ';', '\\', '`',
  '?', '\\', 'Z', 'X', 'C', 'V', 'B',
  'N', 'M', ',', '.', '/', '?', '?',
  '?', ' '
};
#define BACKSPACE 0x0E
#define ENTER 0x1C

bool backspace(char buffer[]) {
    int len = strlen(buffer);
    if (len > 0) {
        buffer[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

void print_backspace() {
    cursor_backward();
}
void execute_command(char *input) {
    if (lstrcmp(input, "EXIT") == 0) {
        scrprint("Stopping the CPU. Bye!\n");
        __asm__ volatile("hlt");
    }
    scrprint("Unknown command: ");
    scrprint(input);
    scrprint("\n> ");
}

void keyboardCallback() {
    uint8_t scancode = inb(0x60);

    if (scancode > SC_MAX) return;

    if (scancode == BACKSPACE) {
        if (backspace(key_buffer)) {
            print_backspace();
        }
    } else if (scancode == ENTER) {
        scrprint("\n");
        if (key_buffer == '\0') {key_buffer[0] = '\0'; return;}
        execute_command(key_buffer);
        key_buffer[0] = '\0'; 
     } else {
        char letter = scancode_to_char[(int) scancode];
        append(key_buffer, letter);
        char str[2] = {letter, '\0'};
        scrprint(str);
    }
}