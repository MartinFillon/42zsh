/*
** EPITECH PROJECT, 2022
** my_list
** File description:
** find element
*/

#include "my_list.h"

void *list_find(list_t *list, void *data, int (*cmp)(void *, void *))
{
    if (list->size == 0)
        return NULL;

    for (node_t *n = list->front; n != NULL; n = n->next)
        if (cmp(n->data, data))
            return n->data;

    return NULL;
}
