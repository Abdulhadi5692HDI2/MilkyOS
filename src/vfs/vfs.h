#ifndef _VFS_H
#define _VFS_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


struct file
{
    char* path;
    size_t size;
    char* data;
};



void init_vfs();

void read(struct file f1);
void write(struct file f1, const char data);

#endif