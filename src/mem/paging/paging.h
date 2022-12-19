#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();
void setPaging();