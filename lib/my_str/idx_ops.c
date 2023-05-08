/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** index operations
*/

#include <string.h>

#include "my_str.h"

str_t **str_erase_at_idx(str_t **str, size_t idx)
{
    if (idx >= (*str)->length)
        return str;

    for (size_t i = idx; i < (*str)->length; i++)
        (*str)->data[i] = (*str)->data[i + 1];

    (*str)->length--;
    return str;
}

str_t **str_insert_at_idx(str_t **str, size_t idx, char chr)
{
    if (idx > (*str)->length)
        return str;

    if ((*str)->length + 2 > (*str)->capacity)
        str_resize(str, (*str)->length + 2);

    memmove((*str)->data + idx + 1, (*str)->data + idx, (*str)->length - idx);
    (*str)->length++;
    (*str)->data[(*str)->length] = '\0';
    (*str)->data[idx] = chr;

    return str;
}
