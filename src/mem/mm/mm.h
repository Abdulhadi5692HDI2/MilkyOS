#ifndef _MM_H
#define _MM_H
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct dynamic_mem_node {
    uint32_t size;
    bool used;
    struct dynamic_mem_node *next;
    struct dynamic_mem_node *prev;
} dynamic_mem_node_t;

#define NULL_POINTER ((void*)0)
#define DYNAMIC_MEM_TOTAL_SIZE 4*1024
#define DYNAMIC_MEM_NODE_SIZE sizeof(dynamic_mem_node_t)

static uint8_t dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dynamic_mem_node_t *dynamic_mem_start;

void init_dynamic_mem();

void *m_malloc(size_t size);

void m_free(void *p);

void *merge_next_node_into_current(dynamic_mem_node_t *current_mem_node);
void *merge_current_node_into_previous(dynamic_mem_node_t *current_mem_node);
void cm(const char *string);
int re(int op);
#endif