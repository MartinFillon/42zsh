/*
** EPITECH PROJECT, 2022
** my_str_isalpha.c
** File description:
** returns 1 if every chars of the string is alpha
*/

#include <ctype.h>

int my_str_isalpha(char const *str)
{
    if (*str == '\0')
        return 0;

    while (*str) {
        if (!isalpha(*str))
            return 0;
        str++;
    }

    return 1;
}

int my_str_isupper(char const *str)
{
    if (*str == '\0')
        return 0;

    while (*str) {
        if (!isupper(*str))
            return 0;
        str++;
    }

    return 1;
}

int my_str_isnum(char const *str)
{
    if (*str == '\0')
        return 0;

    while (*str) {
        if (!isdigit(*str))
            return 0;
        str++;
    }

    return 1;
}

int my_str_islower(char const *str)
{
    if (*str == '\0')
        return 0;

    while (*str) {
        if (!islower(*str))
            return 0;
        str++;
    }

    return 1;
}
