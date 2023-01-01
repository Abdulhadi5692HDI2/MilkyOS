#include "vfs.h"
#include "../misc/misc.h"
#include "../kernel.h"

void init_vfs() {
    scrprint("\nvfs: Initalized file system 'tmpfs'!");
}
vfs_op_t create(char* path) {
    struct file new;
    new.path = path;
    new.data = "";
    new.size = 0;    
}
vfs_op_t read(struct file f1) {
    scrprint("\n");
    scrprint(f1.path);
    scrprint("\n");
    scrprint(f1.data);
}
vfs_op_t write(struct file f1, char* data) {
    f1.data = data;
    f1.size = strlen(data);
}
// file just gets replaced with non-existent NULL
vfs_op_t delete(struct file f3) {
    f3.path = "";
    f3.data = "";
    f3.size = 0;
}
void newtmp() {
    struct dir tmp;
    tmp.path = "/tmp";
    tmp.istmp = true;
}