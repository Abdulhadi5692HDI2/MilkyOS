#include "libc/libc.h"
#include <stddef.h>
#include <stdint.h>

void panic(const char* error, const char* process) {
    printf("\n");
    printf("PANIC: ");
    printf(error);
    printf("\nThis error was caused by running process ");
    printf(process);
    printf(". You may open a bug report at https://github.com/Abdulhadi5692HDI2/MilkyOS.git!\n");
    printf("Its safe to hold/press the power button now.");

    __asm__ volatile ("hlt");
}

void panic2(const char* error, const char* process) {
    printf("\n");
    printf("PANIC: ");
    printf(error);
    printf("\nThis error was caused by running process ");
    printf(process);
    printf(". You may open a bug report at https://github.com/Abdulhadi5692HDI2/MilkyOS.git!\n");
    printf("Its safe to hold/press the power button now.");
    // panic handlers may add a custom halt function.
}