#ifndef _MISC_H
#define _MISC_H
#include <stdint.h>
#include <stddef.h>
#include <string.h>

char* itoa(int value, char* result, int base);
extern void *memcpy(void *dest, const void *src, size_t n);
size_t strlen(const char * __s);
void append(char s[], char n);
#endif