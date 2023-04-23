/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** symbols
*/

#include <string.h>

#include "my_cstr.h"

#include "mysh/parser.h"

int is_symbol(char *data)
{
    for (int j = 0; SYMBOLS[j]; ++j)
        if (my_streq(data, SYMBOLS[j]))
            return 1;
    return 0;
}

char *find_symbol(char const *symbol, char *line_at)
{
    if (strncmp(line_at, symbol, strlen(symbol)) == 0)
        return strdup(symbol);
    return NULL;
}
