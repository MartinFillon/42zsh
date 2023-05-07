/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** env
*/

#include <stdlib.h>
#include <string.h>

#include "my_map.h"

map_t *env_create(char const *const *env)
{
    map_t *env_ = map_create(100);
    str_t *key = NULL;
    char *value = NULL;

    for (size_t i = 0; env[i]; ++i) {
        value = strchr(env[i], '=');
        if (value == NULL)
            continue;
        *value++ = '\0';
        key = str_create(env[i]);
        map_set(env_, key, str_create(value));
        free(key);
    }
    return env_;
}
