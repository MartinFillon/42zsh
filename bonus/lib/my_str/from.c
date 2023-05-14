/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** str from int / long int / double
*/

#include <stdio.h>

#include "my_str.h"

str_t *my_itostr(long int nb)
{
    size_t len = snprintf(NULL, 0, "%ld", nb);
    str_t *str = str_screate(len + 1);
    str->length = snprintf(str->data, len + 1, "%ld", nb);

    return str;
}

str_t *my_ftostr(double nb, int precision)
{
    size_t len = snprintf(NULL, 0, "%.*lf", precision, nb);
    str_t *str = str_screate(len + 1);
    str->length = snprintf(str->data, len + 1, "%.*lf", precision, nb);

    return str;
}
