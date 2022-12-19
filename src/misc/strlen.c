#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "misc.h"

size_t strlen(const char * __s) {
    size_t len = 0;
    for (; !!*__s; __s++, len++);
    return len;
}
