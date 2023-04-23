/*
** EPITECH PROJECT, 2022
** navy
** File description:
** convert
*/

#include <stdlib.h>

#include "my_str.h"

long int str_toint(str_t *str)
{
    return atol(str->data);
}

double str_tofloat(str_t *str)
{
    return atof(str->data);
}

char *str_tocstr(str_t *str)
{
    return str->data;
}
