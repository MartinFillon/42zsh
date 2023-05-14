/*
** EPITECH PROJECT, 2022
** my_list
** File description:
** sort
*/

#include "my_list.h"

static int default_compare(void *a, void *b)
{
    return *(int*)a - *(int*)b;
}

void swap_data(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

static node_t *partition(
    int (*cmp)(void *, void *),
    node_t *start, node_t *end
)
{
    node_t *pivot = end;
    node_t *i = start->prev;

    for (node_t *j = start; j != end; j = j->next) {
        if (cmp(j->data, pivot->data) <= 0) {
            i = (i != NULL) ? i->next : start;
            swap_data(&i->data, &j->data);
        }
    }

    i = (i == NULL) ? start : i->next;
    swap_data(&i->data, &end->data);
    return i;
}

static void quicksort(
    int (*cmp)(void *, void *),
    node_t* start, node_t *end
)
{
    if (end == NULL || end == start || start == end->next)
        return;

    node_t *center = partition(cmp, start, end);
    quicksort(cmp, start, center->prev);
    quicksort(cmp, center->next, end);
}

void list_sort(list_t *list, int (*cmp)(void *, void *))
{
    if (cmp == NULL)
        cmp = &default_compare;

    quicksort(cmp, list->front, list->back);
}
