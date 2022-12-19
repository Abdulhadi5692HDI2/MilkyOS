#include "kernel.h"

void panic(const char* error, const char* process) {
    scrprint("\n");
    scrprint("PANIC: ");
    scrprint(error);
    scrprint("\nThis error was caused by running process ");
    scrprint(process);
    scrprint(". You may open a bug report at https://github.com/Abdulhadi5692HDI2/MilkyOS.git!\n");
    scrprint("Its safe to hold/press the power button now.");
    __asm__ volatile ("hlt");
}