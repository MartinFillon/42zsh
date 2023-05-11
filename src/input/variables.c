/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** variables
*/

#include <ctype.h>
#include <stddef.h>
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

static int get_variable(
    str_t **new, char const *line, size_t *i, shell_t *state
)
{
    size_t start = *i;
    size_t skip = line[*i + 1] == '{';
    str_t *var_name = NULL;
    str_t *value = NULL;

    *i += skip;
    while ((isalnum(line[*i + 1]) || line[*i + 1] == '?') && line[*i + 1])
        ++*i;
    if (start == *i)
        return 0;
    var_name = str_ncreate(line + start + 1 + skip, *i - start - skip);
    if ((value = map_get(state->env, var_name)) != NULL ||
        (value = map_get(state->vars, var_name)) != NULL) {
        str_sadd(new, value);
        *i += skip;
        free(var_name);
        return 0;
    }
    dprintf(2, "%s: Undefined variable.\n", str_tocstr(var_name));
    free(var_name);
    return 1;
}

static void trim_cmd_line(str_t *line)
{
    while (str_startswith(line, STR(" ")) || str_startswith(line, STR("\t")) ||
           str_endswith(line, STR(" ")) || str_endswith(line, STR("\t"))) {
        str_trim(&line, ' ');
        str_trim(&line, '\t');
    }
}

str_t *parse_variables(char const *line, shell_t *state)
{
    size_t len = strlen(line);
    str_t *line_ = str_screate(len);
    int error = 0;

    for (size_t i = 0; i < len; ++i) {
        switch (line[i]) {
            case '~': error = add_home(&line_, state->env); break;
            case '$': error = get_variable(&line_, line, &i, state); break;
            default: str_cadd(&line_, line[i]); break;
        }
        if (error) {
            free(line_);
            return NULL;
        }
    }
    trim_cmd_line(line_);
    return line_;
}
