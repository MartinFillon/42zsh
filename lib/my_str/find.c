/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** find functions
*/

#include <string.h>

#include "my_str.h"

long str_find(str_t const *str, str_t *find, size_t start)
{
    if (find->length > str->length)
        return -1;

    if (start >= str->length)
        return -1;

    for (size_t i = start; i < str->length - find->length; ++i)
        if (strcmp(str->data + i, find->data) == 0)
            return i;

    return -1;
}

long str_findlast(str_t const *str, str_t *find)
{
    if (find->length > str->length)
        return -1;

    for (long i = str->length - find->length; i > 0; --i)
        if (strcmp(str->data + i, find->data) == 0)
            return i;

    return -1;
}
