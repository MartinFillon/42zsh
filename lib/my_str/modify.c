/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** modifiers
*/

#include <stdlib.h>
#include <string.h>

#include "my_str.h"

str_t **str_slice(str_t **str, size_t start, size_t end)
{
    for (size_t i = 0; i < end - start; i++)
        (*str)->data[i] = (*str)->data[start + i];

    (*str)->length = end - start;
    (*str)->data[(*str)->length] = '\0';

    return str;
}

str_t *str_reverse(str_t *str)
{
    size_t len = str->length;
    size_t idx = 0;
    char temp;

    while (idx < len / 2) {
        temp = str->data[idx];
        str->data[idx] = str->data[len - idx - 1];
        str->data[len - idx - 1] = temp;
        idx++;
    }

    return str;
}

void str_replace(str_t **str, str_t const *old, str_t const *new)
{
    str_t *new_str = str_screate((*str)->length);

    for (size_t i = 0, j = 0; i < (*str)->length; ++i) {
        if ((*str)->data[i] != old->data[j]) {
            str_cadd(&new_str, (*str)->data[i]);
            j = 0;
            continue;
        }
        ++j;
        if (j == old->length) {
            str_sadd(&new_str, new);
            j = 0;
        }
    }
    free(*str);
    *str = new_str;
}

str_t **str_clear(str_t **str)
{
    memset((*str)->data, 0, sizeof(char) * (*str)->capacity);
    (*str)->length = 0;

    return str;
}
