#ifndef _MEMORY_H
#define _MEMORY_H 1

#include "stdint.h"
#include "stddef.h"
#include "bool.h"

#define MEM_TOTAL_SIZE 4096 // 4 kb
#define MEM_NODE_SIZE sizeof(mem_node_t)

typedef struct mem_node // double linked list
{
    uint32_t size;
    boolean used;
    struct mem_node *next;
    struct mem_node *prev;
} mem_node_t;

void memcpy(void *dest, void *src, size_t n);
void init_mem();
void *find_best_mem_block(mem_node_t *dynamic_mem, size_t size);
void *malloc(size_t size);
void *merge_next_node_into_current(mem_node_t *current_mem_node);
void *merge_current_node_into_previous(mem_node_t *current_mem_node);
void free(void *p);

#endif