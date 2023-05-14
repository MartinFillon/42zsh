/*
** EPITECH PROJECT, 2022
** my_utils
** File description:
** my swap
*/

#include <stddef.h>
#include <string.h>

void my_swap(void *a, void *b, size_t elem_size)
{
    static char temp[1024] = {0};

    if (elem_size > 1024)
        return;

    memcpy(temp, b, elem_size);
    memcpy(b, a, elem_size);
    memcpy(a, temp, elem_size);
}
