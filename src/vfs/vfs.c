#include "vfs.h"
#include "../misc/misc.h"
#include "../kernel.h"
void init_vfs() {
    scrprint("\nvfs: Initalized file system 'tmpfs'!");
}

void read(struct file f1) {
    scrprint("\n");
    scrprint(f1.path);
    scrprint("\n");
    scrprint(f1.data);
}

// file just gets replaced with non-existent NULL
void delete(struct file f3) {
    f3.path = "";
    f3.data = "";
    f3.size = 0;
}