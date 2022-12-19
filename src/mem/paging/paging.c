#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "paging.h" // current directory is <project>/mem/paging

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1045] __attribute__((aligned(4096)));

void setPaging() {
    int i;
    unsigned int a;

    for (i=0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }

    for (a = 0; a < 1024; a++) {
        first_page_table[i] = (i * 0x1000) | 3;
    }
    loadPageDirectory(page_directory);
    enablePaging();

}