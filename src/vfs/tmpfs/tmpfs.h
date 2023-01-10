#ifndef _TMPFS_H
#define _TMPFS_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
struct file {
	char* path;
	char* data;
	size_t size;
};

struct folder {
	char* path;
	bool ismount;
};


void changedir(struct folder f);
void frename(struct file f, const char* newpath);
void fdelete(struct file f);
#endif