/*
** EPITECH PROJECT, 2022
** my_vec
** File description:
** misc
*/

#include <stdlib.h>

#include "my_vec.h"

size_t get_padded_size(size_t size)
{
    size_t size_pad = 128;

    while (size_pad < size)
        size_pad *= 2;

    return size_pad;
}

void *vec_at(void *v, size_t idx)
{
    vec_t *vec = (vec_t *)v;

    return vec->data + idx * vec->_elem_size;
}

vec_t **vec_resize(vec_t **vec, size_t new_size)
{
    size_t new_cap = get_padded_size(new_size);
    vec_t *old = *vec;

    *vec = realloc(old, sizeof(vec_t) + old->_elem_size * new_cap);
    (*vec)->capacity = new_cap;

    return vec;
}
