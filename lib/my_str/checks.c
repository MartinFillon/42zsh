/*
** EPITECH PROJECT, 2022
** antman
** File description:
** checks
*/

#include "my_cstr.h"
#include "my_str.h"

int str_contains(str_t const *str, char c)
{
    for (size_t i = 0; i < str->length; ++i)
        if (str->data[i] == c)
            return 1;

    return 0;
}

int str_startswith(str_t const *str, str_t const *start)
{
    if (str->length < start->length)
        return 0;

    return (str_ncompare(str, start, start->length) == 0);
}

int str_endswith(str_t const *str, str_t const *end)
{
    size_t i = str->length - end->length;
    size_t j = 0;

    while (i < str->length && j < end->length && str->data[i] == end->data[j]) {
        i++;
        j++;
    }

    return i == str->length;
}
