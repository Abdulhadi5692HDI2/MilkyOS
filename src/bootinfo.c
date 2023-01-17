#include "boot/limine.h"
#include "libc/libc.h"
#include <stdint.h>
#include "bootinfo.h"
#include <stddef.h>
static volatile struct limine_bootloader_info_request bootinfo =  {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0
};

void printinfo() {
    char* name = bootinfo.response->name;
    char* ver = bootinfo.response->version;
    scrprint("\nBoot Info: \n");
    scrprint("Name of Bootloader: ");
    scrprint(name);
    scrprint("\nVersion of Bootloader: ");
    scrprint(ver);
    scrprint("\n");

}