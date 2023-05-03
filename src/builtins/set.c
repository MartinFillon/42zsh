/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** set
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/builtins.h"
#include "mysh/mysh.h"

void builtin_set(vec_str_t *av, shell_t *state)
{
    vec_str_t *tmp = NULL;
    str_t *key = NULL;

    for (size_t i = 0; i < av->size; i++) {
        tmp = str_split(av->data[i], STR("="));
        if ((key = map_get(state->vars, tmp->data[0])) == NULL)
            map_set(
                state->vars, tmp->data[0],
                (tmp->size == 2) ? tmp->data[1] : str_create("\0")
            );
        else
            key = *str_sadd(
                str_clear(&key),
                (tmp->size == 2) ? tmp->data[1] : str_create("\0")
            );
        free(tmp);
    }
}
