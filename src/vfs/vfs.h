#ifndef _VFS_H
#define _VFS_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#define CLOSED true

struct file
{
    char* path;
    char* data;
    size_t size;
    bool close;
};



void init_vfs();

void read(struct file f1);
void write(struct file f2, const char* data2);
void delete(struct file f3);
void close(struct file f4);
#endif