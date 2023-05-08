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

#include "mysh/mysh.h"

static const char *ALPHA_CHARS =
    "setenv: Variable name must contain alphanumeric characters.\n";
static const char *TOO_FEW = "unsetenv: Too few arguments.\n";
static const char *TOO_MANY = "setenv: Too many arguments.\n";
static const char *BEGIN_WITH_LETTER =
    "setenv: Variable name must begin with a letter.\n";

int builtin_env(vec_str_t UNUSED *av, shell_t *state)
{
    vec_str_t *keys = map_get_keys(state->env);

    for (size_t i = 0; i < keys->size; ++i) {
        printf(
            "%s=%s\n", str_tocstr(keys->data[i]),
            str_tocstr(map_get(state->env, keys->data[i]))
        );
    }

    vec_free(keys);
    return 0;
}

static void update_value(shell_t *state, vec_str_t *av)
{
    if (map_get(state->env, av->data[1]) != NULL)
        free(map_get(state->env, av->data[1]));
    map_set(
        state->env, av->data[1],
        (av->size == 2) ? str_create("") : str_dup(av->data[2])
    );
}

int builtin_setenv(vec_str_t *av, shell_t *state)
{
    if (av->size == 1)
        return builtin_env(av, state);
    if (av->size == 2 || av->size == 3) {
        if (!isalpha(av->data[1]->data[0])) {
            dprintf(2, "%s", BEGIN_WITH_LETTER);
            return 1;
        }
        if (!str_isalphanum(av->data[1])) {
            dprintf(2, "%s", ALPHA_CHARS);
            return 1;
        }
        update_value(state, av);
        return 0;
    }
    dprintf(2, "%s", TOO_MANY);
    return 1;
}

int builtin_unsetenv(vec_str_t *av, shell_t *state)
{
    if (av->size < 2) {
        dprintf(2, "%s", TOO_FEW);
        return 1;
    }
    for (size_t i = 1; i < av->size; ++i) {
        if (map_get(state->env, av->data[i]) != NULL) {
            free(map_get(state->env, av->data[i]));
            map_del(state->env, av->data[i]);
        }
    }
    return 0;
}
