#include "../include/memory.h"
#include "../include/string.h"
#include "../include/tty.h"

void memcpy(void *dest, void *src, size_t n)
{
    // Typecast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // Copy contents of src[] to dest[]
    for (int i = 0; i < n; i++)
        cdest[i] = csrc[i];
}

void heap_init()
{
    printf("\nInitializing heap ...");

    int total_table_entries = HEAP_SIZE_BYTES / HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY *)HEAP_TABLE_ADRESS;
    kernel_heap_table.total = total_table_entries;

    void *end = (void *)(HEAP_ADDRESS + HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void *)HEAP_ADDRESS, end, &kernel_heap_table);
    if (res < 0)
    {
        printf("\nKernel panic: Failed to create heap");
    }

    printf("\nHeap initialized.");
}

static int heap_validate_alignment(void *ptr)
{
    return ((int)ptr % HEAP_BLOCK_SIZE) == 0;
}

static int heap_validate_table(void *ptr, void *end, struct heap_table *table)
{
    int res = true;

    size_t table_size = (size_t)(end - ptr);
    size_t total_blocks = table_size / HEAP_BLOCK_SIZE;

    if (table->total != total_blocks)
    {
        res = -EINVARG;
        goto out;
    }

out:
    return res;
}

int heap_create(struct heap *heap, void *ptr, void *end, struct heap_table *table)
{
    int res = 0;

    if (!heap_validate_alignment(ptr) || !heap_validate_alignment(end))
    {
        res = -EINVARG;
        goto out;
    }

    memset(heap, 0, sizeof(struct heap));
    heap->saddr = ptr;
    heap->table = table;

    res = heap_validate_table(ptr, end, table);
    if (res == false)
    {
        goto out;
    }

    size_t table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total;
    memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

out:

    return res;
}

static uint32_t heap_align_value_to_upper(uint32_t val)
{
    if (val % HEAP_BLOCK_SIZE == 0)
    {
        return val;
    }

    val = (val - (val % HEAP_BLOCK_SIZE));
    val += HEAP_BLOCK_SIZE;
    return val;
}

static int heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry)
{
    return entry & 0x0f;
}

int heap_get_start_block(struct heap *heap, uint32_t total_blocks)
{
    struct heap_table *table = heap->table;
    int bc = 0;
    int bs = -1;
    size_t i;

    for (i = 0; i < table->total; i++)
    {
        if (heap_get_entry_type(table->entries[i] != HEAP_BLOCK_TABLE_ENTRY_FREE))
        {
            bc = 0;
            bs = -1;
            continue;
        }
        // first block
        if (bs == -1)
        {
            bs = i;
        }
        bc++;
        if (bc == total_blocks)
        {
            break;
        }
    }

    if (bs == -1)
    {
        return -ENOMEM;
    }
    return bs;
}

void *heap_block_to_adress(struct heap *heap, uint32_t block)
{
    return heap->saddr + (block * HEAP_BLOCK_SIZE);
}

void heap_mark_blocks_taken(struct heap *heap, int start_block, int total_blocks)
{
    int end_block = (start_block + total_blocks) - 1;
    int i;

    HEAP_BLOCK_TABLE_ENTRY entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_IS_FIRST;

    if (total_blocks > 1)
    {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    for (i = start_block; i <= end_block; i++)
    {
        heap->table->entries[i] = entry;
        entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        if (i != end_block - 1)
        {
            entry |= HEAP_BLOCK_HAS_NEXT;
        }
    }
}

void *heap_malloc_blocks(struct heap *heap, uint32_t total_blocks)
{
    void *address = 0;

    int start_block = heap_get_start_block(heap, total_blocks);
    if (start_block < 0)
    {
        printf("\nError getting block");
        goto out;
    }

    address = heap_block_to_adress(heap, start_block);

    heap_mark_blocks_taken(heap, start_block, total_blocks);

out:
    return address;
}

void heap_mark_blocks_free(struct heap *heap, int starting_block)
{
    struct heap_table *table = heap->table;
    int i;

    for (i = starting_block; i < (int)table->total; i++)
    {
        HEAP_BLOCK_TABLE_ENTRY entry = table->entries[i];
        table->entries[i] = HEAP_BLOCK_TABLE_ENTRY_FREE;
        if (!(entry & HEAP_BLOCK_HAS_NEXT))
        {
            break;
        }
    }
}

int heap_address_to_block(struct heap *heap, void *address)
{
    return ((int)(address - heap->saddr) / HEAP_BLOCK_SIZE);
}

void *heap_malloc(struct heap *heap, size_t size)
{
    size_t aligned_size = heap_align_value_to_upper(size);
    uint32_t total_blocks = aligned_size / HEAP_BLOCK_SIZE;

    return heap_malloc_blocks(heap, total_blocks);
}

void heap_free(struct heap *heap, void *ptr)
{
    heap_mark_blocks_free(heap, heap_address_to_block(heap, ptr));
}

void *kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size);
}

void kfree(void *ptr)
{
    heap_free(&kernel_heap, ptr);
}