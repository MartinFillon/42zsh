/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** my_vfree
*/

#include <stdarg.h>
#include <stdlib.h>

void my_vfree(int ac, ...)
{
    va_list ap;

    va_start(ap, ac);
    while (ac--)
        free(va_arg(ap, void *));
    va_end(ap);
}
