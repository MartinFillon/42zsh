/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** trim
*/

#include "my_str.h"

str_t **str_ltrim(str_t **str, char pad)
{
    size_t start = 0;

    while ((*str)->data[start] == pad && start < (*str)->length)
        start++;

    str_slice(str, start, (*str)->length);

    return str;
}

str_t **str_rtrim(str_t **str, char pad)
{
    size_t end = (*str)->length - 1;

    while ((*str)->data[end] == pad && end > 0)
        end--;

    str_slice(str, 0, end + 1);

    return str;
}

str_t **str_trim(str_t **str, char pad)
{
    str_ltrim(str, pad);
    str_rtrim(str, pad);

    return str;
}
