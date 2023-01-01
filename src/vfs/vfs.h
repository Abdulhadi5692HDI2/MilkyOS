#ifndef _VFS_H
#define _VFS_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef size_t byte_t;
struct file
{
    char* path;
    char* data;
    byte_t size; //
};
struct dir
{
    char* path;
    bool* istmp;
};

typedef void vfs_op_t;

void init_vfs();

vfs_op_t create(char* path);
vfs_op_t read(struct file f1);
vfs_op_t write(struct file f1, char* data);
vfs_op_t delete(struct file f1);
void newtmp();
#endif