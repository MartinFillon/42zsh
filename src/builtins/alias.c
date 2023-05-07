/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_map.h"
#include "my_str.h"
#include "my_utils.h"
#include "my_vec.h"

#include "mysh/mysh.h"

static str_t *join_argv(vec_str_t *av)
{
    str_t *joined_argv = str_create("");

    for (size_t i = 2; i < av->size; ++i) {
        str_sadd(&joined_argv, av->data[i]);
        str_cadd(&joined_argv, ' ');
    }

    return joined_argv;
}

int builtin_alias(vec_str_t *av, shell_t *state)
{
    if (av->size < 3)
        return 1;

    str_t *name = av->data[1];
    str_t *value = join_argv(av);

    if (map_get(state->alias, name) != NULL)
        free(map_get(state->alias, name));

    map_set(state->alias, name, value);
    return 0;
}
