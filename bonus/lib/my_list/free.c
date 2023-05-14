/*
** EPITECH PROJECT, 2022
** my_list
** File description:
** list free
*/

#include <stdlib.h>

#include "my_list.h"

void list_free_fn(list_t *list, void (*free_fn)(void *))
{
    node_t *temp = list->front;
    node_t *old = NULL;

    while (temp != NULL) {
        old = temp;
        temp = temp->next;
        free_fn(old->data);
        free(old);
    }
    free(list);
}

void list_free(list_t *list)
{
    list_free_fn(list, &free);
}
