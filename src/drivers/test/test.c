#include <stdint.h>
#include <stddef.h>
#include "../../kernel.h"
#include "test.h"



#define SUCCESS 0
#define FAIL 1

int testInit() {
    scrprint(" Test Driver loaded\n");
    return SUCCESS;
}
