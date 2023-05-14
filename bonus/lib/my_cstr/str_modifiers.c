/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** puts every letter in lowercase/uppercase
*/

#include <ctype.h>
#include <stddef.h>

char *my_strlowcase(char *str)
{
    for (size_t i = 0; str[i]; i++)
        str[i] = tolower(str[i]);

    return str;
}

char *my_strupcase(char *str)
{
    for (size_t i = 0; str[i]; i++)
        str[i] = toupper(str[i]);

    return str;
}
