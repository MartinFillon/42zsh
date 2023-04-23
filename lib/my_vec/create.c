/*
** EPITECH PROJECT, 2022
** my_vec
** File description:
** vector
*/

#include <stdlib.h>

#include "my_vec.h"

void *vec_create(size_t nb_data, size_t el_size)
{
    size_t capacity = get_padded_size(nb_data);
    vec_t *vec = malloc(sizeof(vec_t) + el_size * capacity);

    if (vec == NULL)
        return NULL;

    vec->size = 0;
    vec->capacity = capacity;
    vec->_elem_size = el_size;

    return vec;
}
