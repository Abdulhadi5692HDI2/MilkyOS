#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limine.h>
#include <mem/pmem/pmem.h>

__attribute__((section(".limine_reqs")))
struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0, .response = NULL
};
void *memmap_req = &memmap_request;


typedef struct dmn {
    uint32_t size;
    bool used;
    struct dmn *next;
    struct dmn *prev;
} dmn_t;

#define DYNAMIC_MEM_TOTAL_SIZE 4*1024 // total size 4GB
#define DYNAMIC_MEM_NODE_SIZE sizeof(dmn_t)

static uint8_t dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dmn_t *dynamic_mem_start;

void init_dynamic_mem() {
    dynamic_mem_start = (dmn_t *) dynamic_mem_area;
    dynamic_mem_start->size = DYNAMIC_MEM_TOTAL_SIZE - DYNAMIC_MEM_NODE_SIZE;
    dynamic_mem_start->next = NULL;
    dynamic_mem_start->prev = NULL;
}
void *merge_next_node_into_current(dmn_t *current_mem_node) {
    dmn_t *next_mem_node = current_mem_node->next;
    if (next_mem_node != NULL && !next_mem_node->used) {
        // add size of next block to current block
        current_mem_node->size += current_mem_node->next->size;
        current_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        // remove next block from list
        current_mem_node->next = current_mem_node->next->next;
        if (current_mem_node->next != NULL) {
            current_mem_node->next->prev = current_mem_node;
        }
    }
    return current_mem_node;
}

void *merge_current_node_into_previous(dmn_t *current_mem_node) {
    dmn_t *prev_mem_node = current_mem_node->prev;
    if (prev_mem_node != NULL && !prev_mem_node->used) {
        // add size of previous block to current block
        prev_mem_node->size += current_mem_node->size;
        prev_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        // remove current node from list
        prev_mem_node->next = current_mem_node->next;
        if (current_mem_node->next != NULL) {
            current_mem_node->next->prev = prev_mem_node;
        }
    }
    return current_mem_node;
}

void *find_best_mem_block(dmn_t *dynamic_mem, size_t size) {
    // initialize the result pointer with NULL and an invalid block size
    dmn_t *best_mem_block = (dmn_t *) NULL;
    uint32_t best_mem_block_size = DYNAMIC_MEM_TOTAL_SIZE + 1;

    // start looking for the best (smallest unused) block at the beginning
    dmn_t *current_mem_block = dynamic_mem;
    while (current_mem_block) {
        // check if block can be used and is smaller than current best
        if ((!current_mem_block->used) &&
            (current_mem_block->size >= (size + DYNAMIC_MEM_NODE_SIZE)) &&
            (current_mem_block->size <= best_mem_block_size)) {
            // update best block
            best_mem_block = current_mem_block;
            best_mem_block_size = current_mem_block->size;
        }

        // move to next block
        current_mem_block = current_mem_block->next;
    }
    return best_mem_block;
}

void *malloc(size_t size) {
    dmn_t *best_mem_block =
            (dmn_t *) find_best_mem_block(dynamic_mem_start, size);

    // check if we actually found a matching (free, large enough) block
    if (best_mem_block != NULL) {
        // subtract newly allocated memory (incl. size of the mem node) from selected block
        best_mem_block->size = best_mem_block->size - size - DYNAMIC_MEM_NODE_SIZE;

        // create new mem node after selected node, effectively splitting the memory region
        dmn_t *mem_node_allocate = (dmn_t *) (((uint8_t *) best_mem_block) +
                                                                        DYNAMIC_MEM_NODE_SIZE +
                                                                        best_mem_block->size);
        mem_node_allocate->size = size;
        mem_node_allocate->used = true;
        mem_node_allocate->next = best_mem_block->next;
        mem_node_allocate->prev = best_mem_block;

        // reconnect the doubly linked list
        if (best_mem_block->next != NULL) {
            best_mem_block->next->prev = mem_node_allocate;
        }
        best_mem_block->next = mem_node_allocate;

        // return pointer to newly allocated memory (right after the new list node)
        return (void *) ((uint8_t *) mem_node_allocate + DYNAMIC_MEM_NODE_SIZE);
    }

    return NULL;
}
void free(void *p) {
    // move along, nothing to free here
    if (p == NULL) {
        return;
    }

    // get mem node associated with pointer
    dmn_t *current_mem_node = (dmn_t *) ((uint8_t *) p - DYNAMIC_MEM_NODE_SIZE);

    // pointer we're trying to free was not dynamically allocated it seems
    if (current_mem_node == NULL) {
        return;
    }

    // mark block as unused
    current_mem_node->used = false;

    // merge unused blocks
    current_mem_node = merge_next_node_into_current(current_mem_node);
    merge_current_node_into_previous(current_mem_node);
}

