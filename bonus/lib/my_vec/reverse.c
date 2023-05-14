/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** vec reverse
*/

#include "my_utils.h"
#include "my_vec.h"

void vec_reverse(void *vec)
{
    vec_t *v = vec;

    for (size_t i = 0, j = v->size - 1; i < j; ++i, --j) {
        my_swap(vec_at(v, i), vec_at(v, j), v->_elem_size);
    }
}
