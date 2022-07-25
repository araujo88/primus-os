#include "../include/memory.h"

static uint8_t mem_area[MEM_TOTAL_SIZE];
static mem_node_t *mem_start;

void init_mem()
{
    mem_start = (mem_node_t *)mem_area;
    mem_start->size = MEM_TOTAL_SIZE - MEM_NODE_SIZE;
    mem_start->next = NULL;
    mem_start->prev = NULL;
}

void *find_best_mem_block(mem_node_t *dynamic_mem, size_t size)
{
    // initialize the result pointer with NULL and an invalid block size
    mem_node_t *best_mem_block = (mem_node_t *)NULL;
    uint32_t best_mem_block_size = MEM_NODE_SIZE + 1;

    // start looking for the best (smallest unused) block at the beginning
    mem_node_t *current_mem_block = dynamic_mem;
    while (current_mem_block)
    {
        // check if block can be used and is smaller than current best
        if ((!current_mem_block->used) &&
            (current_mem_block->size >= (size + MEM_NODE_SIZE)) &&
            (current_mem_block->size <= best_mem_block_size))
        {
            // update best block
            best_mem_block = current_mem_block;
            best_mem_block_size = current_mem_block->size;
        }

        // move to next block
        current_mem_block = current_mem_block->next;
    }
    return best_mem_block;
}

void *malloc(size_t size)
{
    mem_node_t *best_mem_block =
        (mem_node_t *)find_best_mem_block(mem_start, size);

    // check if we actually found a matching (free, large enough) block
    if (best_mem_block != NULL)
    {
        // subtract newly allocated memory (incl. size of the mem node) from selected block
        best_mem_block->size = best_mem_block->size - size - MEM_NODE_SIZE;

        // create new mem node after selected node, effectively splitting the memory region
        mem_node_t *mem_node_allocate = (mem_node_t *)(((uint8_t *)best_mem_block) +
                                                       MEM_NODE_SIZE +
                                                       best_mem_block->size);
        mem_node_allocate->size = size;
        mem_node_allocate->used = true;
        mem_node_allocate->next = best_mem_block->next;
        mem_node_allocate->prev = best_mem_block;

        // reconnect the doubly linked list
        if (best_mem_block->next != NULL)
        {
            best_mem_block->next->prev = mem_node_allocate;
        }
        best_mem_block->next = mem_node_allocate;

        // return pointer to newly allocated memory (right after the new list node)
        return (void *)((uint8_t *)mem_node_allocate + MEM_NODE_SIZE);
    }

    return NULL;
}

void *merge_next_node_into_current(mem_node_t *current_mem_node)
{
    mem_node_t *next_mem_node = current_mem_node->next;
    if (next_mem_node != NULL && !next_mem_node->used)
    {
        // add size of next block to current block
        current_mem_node->size += current_mem_node->next->size;
        current_mem_node->size += MEM_NODE_SIZE;

        // remove next block from list
        current_mem_node->next = current_mem_node->next->next;
        if (current_mem_node->next != NULL)
        {
            current_mem_node->next->prev = current_mem_node;
        }
    }
    return current_mem_node;
}

void *merge_current_node_into_previous(mem_node_t *current_mem_node)
{
    mem_node_t *prev_mem_node = current_mem_node->prev;
    if (prev_mem_node != NULL && !prev_mem_node->used)
    {
        // add size of previous block to current block
        prev_mem_node->size += current_mem_node->size;
        prev_mem_node->size += MEM_NODE_SIZE;

        // remove current node from list
        prev_mem_node->next = current_mem_node->next;
        if (current_mem_node->next != NULL)
        {
            current_mem_node->next->prev = prev_mem_node;
        }
    }
    return current_mem_node;
}

void free(void *p)
{
    // move along, nothing to free here
    if (p == NULL)
    {
        return;
    }

    // get mem node associated with pointer
    mem_node_t *current_mem_node = (mem_node_t *)((uint8_t *)p - MEM_NODE_SIZE);

    // pointer we're trying to free was not dynamically allocated it seems
    if (current_mem_node == NULL)
    {
        return;
    }

    // mark block as unused
    current_mem_node->used = false;

    // merge unused blocks
    current_mem_node = merge_next_node_into_current(current_mem_node);
    merge_current_node_into_previous(current_mem_node);
}

void memcpy(void *dest, void *src, size_t n)
{
    // Typecast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // Copy contents of src[] to dest[]
    for (int i = 0; i < n; i++)
        cdest[i] = csrc[i];
}