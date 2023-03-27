#include "../include/shell_history.h"

node_t *create_new_node(char buffer[BUFFER_SIZE])
{
    node_t *result = (node_t *)kmalloc(sizeof(node_t));
    strcpy(result->buffer, buffer);
    result->next = NULL;
    return result;
}

void print_history(node_t *head)
{
    node_t *temporary = head;

    printf("\n");
    while (temporary != NULL)
    {
        printf("%s\n", temporary->buffer);
        temporary = temporary->next;
    }
}

void *insert_at_head(node_t **head, node_t *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
}