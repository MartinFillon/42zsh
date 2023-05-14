/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** string setters
*/

#include <stdarg.h>
#include <string.h>

#include "my_cstr.h"
#include "my_str.h"
#include "my_vec.h"

str_t **str_add(str_t **str, char const *new)
{
    size_t new_len = strlen(new);

    if ((*str)->length + new_len + 1 > (*str)->capacity)
        str_resize(str, (*str)->length + new_len + 1);

    memcpy((*str)->data + (*str)->length, new, new_len);
    (*str)->length += new_len;
    (*str)->data[(*str)->length] = '\0';

    return str;
}

str_t **str_sadd(str_t **str, str_t const *new)
{
    if ((*str)->length + new->length + 1 > (*str)->capacity)
        str_resize(str, (*str)->length + new->length + 1);

    memcpy((*str)->data + (*str)->length, new->data, new->length);
    (*str)->length += new->length;
    (*str)->data[(*str)->length] = '\0';

    return str;
}

str_t **str_cadd(str_t **str, char const new)
{
    if ((*str)->length + 2 > (*str)->capacity)
        str_resize(str, (*str)->length + 2);

    (*str)->data[(*str)->length] = new;
    (*str)->length++;
    (*str)->data[(*str)->length] = '\0';

    return str;
}

str_t **str_vadd(str_t **str, int argc, ...)
{
    va_list ap;

    va_start(ap, argc);
    while (argc--)
        str_add(str, va_arg(ap, char *));
    va_end(ap);

    return str;
}

str_t **str_nadd(str_t **str, char const *new, size_t n)
{
    if ((*str)->length + n + 1 > (*str)->capacity)
        str_resize(str, (*str)->length + n + 1);

    memcpy((*str)->data + (*str)->length, new, n);
    (*str)->length += n;
    (*str)->data[(*str)->length] = '\0';

    return str;
}
