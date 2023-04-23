/*
** EPITECH PROJECT, 2022
** my_stdio
** File description:
** list utils
*/

#include "my_list.h"

void list_insert(list_t *list, node_t *after, void *data)
{
    if (after == NULL || after == list->back) {
        list_pushback(list, data);
        return;
    }
    node_t *new = node_create();
    new->data = data;
    new->next = after->next;
    new->prev = after;
    after->next->prev = new;
    after->next = new;
    list->size++;
}

void list_pushfront(list_t *list, void *data)
{
    node_t *node = node_create();
    node->data = data;
    list->size++;

    if (list->front == NULL && list->back == NULL) {
        list->front = node;
        list->back = node;
    } else {
        node->next = list->front;
        list->front->prev = node;
        list->front = node;
    }
}

void list_pushback(list_t *list, void *data)
{
    node_t *node = node_create();
    node->data = data;
    list->size++;

    if (list->front == NULL && list->back == NULL) {
        list->front = node;
        list->back = node;
    } else {
        node->prev = list->back;
        list->back->next = node;
        list->back = node;
    }
}
