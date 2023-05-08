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

char *exclamation_conditions(history_t *history, str_t *command);

static int get_exclamation(char const *line, shell_t *state)
{
    str_t *designator = str_create(line);
    char *res = NULL;

    if (str_startswith(str_create(line), STR("!")) == 1 && line[1] != '\0'){
        str_erase_at_idx(&designator, 0);
        res = exclamation_conditions(&state->history, designator);
        if (res)
            printf("%s\n", res);
    }
    str_erase_at_idx(&designator, 0);
    dprintf(2, "%s: Event not found.\n", designator->data);
    return 1;
}

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
    size_t start = ++*i;
    str_t *var_name = NULL;
    str_t *value = NULL;

    while (isalnum(line[*i + 1]) && line[*i + 1] != '\0')
        ++*i;
    var_name = str_ncreate(line + start, *i + 1 - start);
    if ((value = map_get(state->env, var_name)) != NULL ||
        (value = map_get(state->vars, var_name)) != NULL) {
        str_sadd(new, value);
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
            case '!': error = get_exclamation(line, state); break;
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
