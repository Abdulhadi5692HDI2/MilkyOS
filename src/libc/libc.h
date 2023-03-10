#ifndef _LIBC_H
#define _LIBC_H
#include <stdint.h>
#include <stddef.h>

void printf(const char* format, ...);
char* itoa(int value, char* result, int base);
char* itoa_hex(uint32_t value, char* result, int base);
void *lmemset(char *dst,char src, int n);
extern void *memcpy(void *dest, const void *src, size_t n);
size_t strlen(const char * __s);
int lstrcmp(char s1[],char s2[]);
void append(char s[], char n);
#endif