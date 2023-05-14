/*
** EPITECH PROJECT, 2022
** my_list
** File description:
** remove elements
*/

#include <stdlib.h>

#include "my_list.h"

void list_unlink(list_t *list, node_t *elem)
{
    if (list->front == NULL || list->back == NULL)
        return;
    if (elem->prev != NULL) {
        elem->prev->next = elem->next;
    } else {
        list->front = elem->next;
    }
    if (elem->next != NULL) {
        elem->next->prev = elem->prev;
    } else {
        list->back = elem->prev;
    }
    list->size--;
}

void list_remove(list_t *list, node_t *elem)
{
    list_unlink(list, elem);
    free(elem);
}

void list_popfront(list_t *list)
{
    list_remove(list, list->front);
}

void list_popback(list_t *list)
{
    list_remove(list, list->back);
}
