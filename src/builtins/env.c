/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** env
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_map.h"
#include "my_str.h"
#include "my_utils.h"
#include "my_vec.h"

static const char *ERROR[] = {
    "setenv: Variable name must contain alphanumeric characters.\n",
    "setenv: Too many arguments.\n",
    "unsetenv: Too few arguments.\n",
    "setenv: Variable name must begin with a letter.\n",
};

int builtin_env(vec_str_t UNUSED *av, map_t *env)
{
    vec_str_t *keys = map_get_keys(env);

    for (size_t i = 0; i < keys->size; ++i) {
        printf(
            "%s=%s\n", str_tocstr(keys->data[i]),
            str_tocstr(map_get(env, keys->data[i]))
        );
    }

    vec_free(keys);
    return 0;
}

int builtin_setenv(vec_str_t *av, map_t *env)
{
    if (av->size == 1)
        return builtin_env(av, env);
    if (av->size == 2 || av->size == 3) {
        if (!isalpha(av->data[1]->data[0])) {
            dprintf(2, "%s", ERROR[3]);
            return 1;
        }
        if (!str_isalphanum(av->data[1])) {
            dprintf(2, "%s", ERROR[0]);
            return 1;
        }
        map_set(
            env, str_dup(av->data[1]),
            (av->size == 2) ? str_create("") : str_dup(av->data[2])
        );
        return 0;
    }
    dprintf(2, "%s", ERROR[1]);
    return 1;
}

int builtin_unsetenv(vec_str_t *av, map_t *env)
{
    if (av->size < 2) {
        dprintf(2, "%s", ERROR[2]);
        return 1;
    }

    for (size_t i = 1; i < av->size; ++i)
        map_del(env, av->data[i]);

    return 0;
}
