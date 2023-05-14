/*
** EPITECH PROJECT, 2022
** my_list
** File description:
** linked list
*/

#include <stdlib.h>

#include "my_list.h"

node_t *node_create(void)
{
    node_t *new = malloc(sizeof(node_t));

    if (new == NULL)
        return NULL;

    new->prev = NULL;
    new->next = NULL;
    new->data = NULL;

    return new;
}

list_t *list_create(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list == NULL)
        return NULL;

    list->front = NULL;
    list->back = NULL;
    list->size = 0;

    return list;
}
