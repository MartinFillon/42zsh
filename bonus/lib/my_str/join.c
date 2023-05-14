/*
** EPITECH PROJECT, 2022
** my_vec
** File description:
** join
*/

#include "my_str.h"
#include "my_vec.h"

str_t *str_join(vec_str_t *vec, str_t *delim)
{
    str_t *new = str_create("");

    for (size_t i = 0; i < vec->size; ++i) {
        if (i != 0)
            str_sadd(&new, delim);
        str_sadd(&new, vec->data[i]);
    }

    return new;
}
