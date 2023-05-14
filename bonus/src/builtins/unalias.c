/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** unalias
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

int builtin_unalias(vec_str_t *av, shell_t *state)
{
    if (av->size < 2) {
        dprintf(2, "unalias: too few arguments.\n");
        return 1;
    }

    for (size_t i = 1; i < av->size; ++i) {
        if (map_get(state->alias, av->data[i]) != NULL) {
            free(map_get(state->alias, av->data[i]));
            map_del(state->alias, av->data[i]);
        }
    }
    return 0;
}
