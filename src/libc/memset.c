#include "libc.h"

void *lmemset(char *dst,char src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = src;
	return p;
}