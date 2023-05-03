/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** variables
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysh/mysh.h"

#include "my_map.h"
#include "my_str.h"

static int add_home(str_t **new, map_t *env)
{
    str_t *val = NULL;

    if ((val = map_get(env, STR("HOME"))) != NULL) {
        str_sadd(new, val);
        return 0;
    }

    dprintf(2, "No $home variable set.\n");
    return 1;
}

static int get_variable(str_t **new, char const *line, size_t *i, shell_t *state)
{
    size_t start = ++*i;
    str_t *var_name = NULL;
    str_t *value = NULL;

    while (isalnum(line[*i]) && line[*i] != '\0')
        ++*i;
    var_name = str_ncreate(line + start, *i - start);
    if ((value = map_get(state->env, var_name)) != NULL) {
        str_sadd(new, value);
        free(var_name);
        return 0;
    }
    if ((value = map_get(state->vars, var_name)) != NULL) {
        str_sadd(new, value);
        free(var_name);
        return 0;
    }
    dprintf(2, "%s: Undefined variable.\n", str_tocstr(var_name));
    free(var_name);
    return 1;
}

str_t *parse_variables(char const *line, shell_t *state)
{
    size_t len = strlen(line);
    str_t *new = str_screate(len);
    int error = 0;

    for (size_t i = 0; i < len; ++i) {
        switch (line[i]) {
            case '~': error = add_home(&new, state->env); break;
            case '$': error = get_variable(&new, line, &i, state); break;
            default: str_cadd(&new, line[i]);
        }
        if (error)
            return NULL;
    }
    return new;
}
