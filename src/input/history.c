/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <stdlib.h>
#include <stdio.h>

#include "my_map.h"

map_t *history_create(map_t *env)
{
    int size_history = 0;
    str_t  *size_env = NULL;

    size_env = map_get(env, STR("HISTSIZE"));
    if (size_env == NULL)
        size_history = 100;
    else
        size_history = atoi(str_tocstr(size_env));
    map_t *history = map_create(size_history);
    return history;
}
