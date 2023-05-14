/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** set
*/

#include <ctype.h>
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

    if (cwd)
        map_set(vars, STR("cwd"), str_create(cwd));
    if (term)
        map_set(vars, STR("term"), str_dup(term));
    map_set(vars, STR("prompt"), str_create("\033[1;31m42zsh $>\033[0m "));
    return vars;
}

int builtin_unset(vec_str_t *av, shell_t *state)
{
    if (av->size < 2) {
        dprintf(2, "unset: Too few arguments.\n");
        return 1;
    }
    for (size_t i = 0; i < av->size; i++) {
        if (map_get(state->vars, av->data[i]) != NULL) {
            free(map_get(state->vars, av->data[i]));
            map_del(state->vars, av->data[i]);
        }
    }
    return 0;
}

static void update_value(shell_t *state, str_t *key, str_t *arg, long eq_idx)
{
    if (map_get(state->vars, key) != NULL)
        free(map_get(state->vars, key));
    if (eq_idx == -1) {
        map_set(state->vars, key, str_create(""));
        free(key);
        return;
    }
    map_set(
        state->vars, key, str_substr(arg, eq_idx + 1, arg->length - eq_idx - 1)
    );
    free(key);
}

int builtin_set(vec_str_t *av, shell_t *state)
{
    str_t *key = NULL;

    for (size_t i = 1; i < av->size; i++) {
        if (!isalpha(av->data[i]->data[0])) {
            dprintf(2, "set: Variable name must begin with a letter.");
            return 1;
        }
        long eq_idx = str_find(av->data[i], STR("="), 0);
        key = str_substr(
            av->data[i], 0,
            (eq_idx == -1) ? av->data[i]->length : (size_t)eq_idx
        );
        update_value(state, key, av->data[i], eq_idx);
    }
    return 0;
}
