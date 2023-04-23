/*
** EPITECH PROJECT, 2022
** my_vec
** File description:
** vec sort
*/

#include <stdlib.h>

#include "my_vec.h"

static int default_compare(void const *a, void const *b)
{
    return *(int *)a - *(int *)b;
}

void vec_sort(void *v, int (*cmp)(void const *, void const *))
{
    vec_t *vec = (vec_t *)v;

    if (cmp == NULL)
        cmp = &default_compare;

    qsort(vec->data, vec->size, vec->_elem_size, cmp);
}
