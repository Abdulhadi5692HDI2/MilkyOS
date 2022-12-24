#include "vfs.h"
#include "../misc/misc.h"
#include "../kernel.h"
void init_vfs() {
    // theres temp
    struct file tmp;
    tmp.path = "/tmp";
    tmp.size = strlen(tmp.path);
    tmp.data = "temp";
}

void read(struct file f1) {
    scrprint("\n");
    scrprint(f1.path);
    scrprint(f1.data);
}
void write(struct file f1, const char data) {
    f1.data = data;
}

