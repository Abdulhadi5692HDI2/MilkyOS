#include "tmpfs.h"
#include "../../libc/libc.h"
#include "../../tty.h"

void changedir(struct folder f) {
	printf("Current directory is: ");
	printf(f.path);
} 
void frename(struct file f, const char* newpath) {
	f.path = newpath;
}
void fdelete(struct file f) {
	f.data = "";
	f.size = 0;
	f.path = "";
}
