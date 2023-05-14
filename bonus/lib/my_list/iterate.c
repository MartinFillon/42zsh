/*
** EPITECH PROJECT, 2022
** my_list
** File description:
** iterators
*/

#include "my_list.h"

void list_foreach(list_t *list, void (*fn)(void *, void *), void *data)
{
    if (list->size == 0)
        return;

    for (node_t *n = list->front; n != NULL; n = n->next)
        fn(n->data, data);
}
