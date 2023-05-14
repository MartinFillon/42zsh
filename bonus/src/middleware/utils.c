/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** utils
*/

#include <stdlib.h>

#include "my_str.h"

char *trim_string(char *data)
{
    str_t *file_ = str_create(data);
    str_trim(&file_, ' ');
    str_trim(&file_, '\t');
    char *file = strdup(str_tocstr(file_));
    free(file_);

    return file;
}
