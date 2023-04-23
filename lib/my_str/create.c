/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** string class
*/

#include <stdlib.h>
#include <string.h>

#include "my_cstr.h"
#include "my_str.h"

str_t *str_screate(size_t n)
{
    size_t capacity = get_padded_size(n);
    str_t *str = malloc(sizeof(str_t) + sizeof(char) * capacity);

    if (str == NULL)
        return NULL;

    str->length = 0;
    str->capacity = capacity;

    return str;
}

str_t *str_ncreate(char const *init, size_t n)
{
    str_t *str = str_screate(n + 1);

    if (str == NULL)
        return NULL;

    str->length = n;
    memcpy(str->data, init, sizeof(char) * n);
    str->data[str->length] = '\0';

    return str;
}

str_t *str_create(char const *init)
{
    size_t len = strlen(init);

    return str_ncreate(init, len);
}

str_t *str_dup(str_t const *old)
{
    str_t *new = str_ncreate(old->data, old->length);

    return new;
}

str_t *str_substr(str_t const *str, size_t start, size_t n)
{
    return str_ncreate(str->data + start, n);
}
