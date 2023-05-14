/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** print
*/

#include <unistd.h>

#include "my_str.h"

void str_print(str_t const *str)
{
    write(1, str->data, str->length);
}

void str_println(str_t const *str)
{
    write(1, str->data, str->length);
    write(1, "\n", 1);
}

void str_dprint(int fd, str_t const *str)
{
    write(fd, str->data, str->length);
}
