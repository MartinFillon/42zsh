/*
** EPITECH PROJECT, 2022
** my_vec
** File description:
** free vector
*/

#include <stdlib.h>

#include "my_vec.h"

void vec_free_fn(void *vec, void (*free_fn)(void *))
{
    vec_void_t *v = (vec_void_t *)vec;

    for (size_t i = 0; i < v->size; i++)
        free_fn(v->data[i]);
    free(v);
}

void vec_free(void *vec)
{
    vec_free_fn(vec, &free);
}
