/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** set
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>

#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/builtins.h"
#include "mysh/mysh.h"

map_t *vars_create(map_t *env)
{
    static char PATHNAME[MAXPATHLEN] = "";
    map_t *vars = map_create(100);
    char *cwd = getcwd(PATHNAME, MAXPATHLEN);
    str_t *term = map_get(env, STR("TERM"));

    map_set(vars, STR("cwd"), str_create(cwd));
    map_set(vars, STR("term"), str_dup(term));
    return vars;
}

void builtin_set(vec_str_t *av, shell_t *state)
{
    vec_str_t *tmp = NULL;
    str_t *key = NULL;

    for (size_t i = 0; i < av->size; i++) {
        tmp = str_split(av->data[i], STR("="));
        if ((key = map_get(state->vars, tmp->data[0])) == NULL)
            map_set(
                state->vars, tmp->data[0],
                (tmp->size == 2) ? str_dup(tmp->data[1]) : str_create("")
            );
        else
            key = *str_sadd(
                str_clear(&key),
                (tmp->size == 2) ? str_dup(tmp->data[1]) : str_create("")
            );
        vec_free(tmp);
    }
}
