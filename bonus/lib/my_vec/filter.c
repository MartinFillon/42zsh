/*
** EPITECH PROJECT, 2022
** my_vec
** File description:
** filter
*/

#include "my_vec.h"

vec_t *vec_filter(void *v, int (*keep)(void *))
{
    vec_t *vec = (vec_t *)v;
    vec_t *new = vec_create(vec->size, vec->_elem_size);

    if (new == NULL)
        return NULL;

    for (size_t i = 0; i < vec->size; ++i)
        if (keep(vec_at(vec, i)))
            vec_pushback(&new, vec_at(vec, i));

    return new;
}
