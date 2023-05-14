/*
** EPITECH PROJECT, 2022
** navy
** File description:
** convert
*/

#include <stdlib.h>

#include "my_str.h"

long int str_toint(str_t const *str)
{
    return atol(str->data);
}

double str_tofloat(str_t const *str)
{
    return atof(str->data);
}

char const *str_tocstr(str_t const *str)
{
    return str->data;
}
