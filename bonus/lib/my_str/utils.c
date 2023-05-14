/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** misc
*/

#include <stdlib.h>
#include <string.h>

#include "my_str.h"
#include "my_utils.h"
#include "my_vec.h"

str_t **str_resize(str_t **str, size_t new_size)
{
    size_t new_cap = get_padded_size(new_size);
    str_t *old = *str;

    *str = realloc(old, sizeof(str_t) + sizeof(char) * new_cap);
    (*str)->capacity = new_cap;

    return str;
}
