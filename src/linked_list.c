#include <dev_elf.h>


llist_t *llist_create()
{
    llist_t *llist = malloc(sizeof(llist_t));
    if (NULL == llist)
    {
        return NULL;
    }

    llist->head = NULL;
    return llist;
}

node_t *node_create(void *data)
{
    if (NULL == data)
    {
        return NULL;
    }

    node_t *node = calloc(1, sizeof(node_t));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

int llist_add_node(llist_t *llist, node_t *node)
{
    if (NULL == llist || NULL == node)
    {
        return FAILURE;
    }

    if (NULL == llist->head)
    {
        llist->head = node;
        return SUCCESS;
    }

    node_t *curr_node = llist->head;
    while(NULL != curr_node->next)
    {
        curr_node = curr_node->next;
    }
    curr_node->next = node;
    return SUCCESS;
}

int llist_add_data(llist_t *llist, void *data)
{
    if (NULL == llist || NULL == data)
    {
        return FAILURE;
    }

    node_t *node = node_create(data);
    if (NULL == node)
    {
        return FAILURE;
    }

    if (FAILURE == llist_add_node(llist, node))
    {
        return FAILURE;
    }
    return SUCCESS;
}

int free_llist(llist_t *llist, void (*free_node_func)())
{
    if (NULL == llist)
    {
        return FAILURE;
    }

    if (NULL == free_node_func)
    {
        free_node_func = &free;
    }

    if (NULL == llist->head)
    {
        free(llist);
        llist = NULL;
        return SUCCESS;
    }

    node_t *curr_node = llist->head;
    node_t *prev_node = NULL;

    while (NULL != curr_node)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
        free_node_func(prev_node);
        prev_node = NULL;
    }

    free(llist);
    llist = NULL;

    return SUCCESS;
}