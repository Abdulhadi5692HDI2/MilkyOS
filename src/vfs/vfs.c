#include "vfs.h"
#include "../misc/misc.h"
#include "../kernel.h"
void init_vfs() {
    scrprint("\nvfs: Initalized file system 'tmpfs'!");
}

void read(struct file f1) {
    if (f1.path == "") {
        scrprint("\nread: error: File does not exist!");
    } else if (f1.data == "")
    {
        scrprint("\nread: error: File data not found!");
    } /*else if (f1.size == 0)
    {
        scrprint("\nread: error: File size not defined!");
    }*/
    
    
    scrprint("\n");
    scrprint(f1.path);
    scrprint("\n");
    scrprint(f1.data);
}

void write(struct file f2, const char* data2) {
    if (f2.path == "") {
        scrprint("\nwrite: error: File does not exist!");
    }
	f2.data = data2;
    f2.size = strlen(data2);
}

// file just gets replaced with non-existent NULL
void delete(struct file f3) {
    f3.path = "";
    f3.data = "";
    f3.size = 0;
    f3.close = CLOSED;
}

void close(struct file f4) {
    // TODO: add some code for future purposes
    f4.close = CLOSED;
}
