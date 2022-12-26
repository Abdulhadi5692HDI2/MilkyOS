#ifndef _VFS_H
#define _VFS_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


struct file
{
    char* path;
    char* data;
    size_t size;
};



void init_vfs();

void read(struct file f1);
void delete(struct file f3);
#endif