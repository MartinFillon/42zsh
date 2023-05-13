/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** foreach
*/

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_btree.h"
#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"

int script_foreach(
    shell_t *state, str_t *var, vec_str_t *list, long int offset
);
int piped_foreach(shell_t *state, str_t *var, vec_str_t *list);

static str_t *get_var_name(str_t *line)
{
    str_t *var = str_create("");
    long i = STR("foreach")->length + 1;

    while (isalpha(line->data[i]) && line->data[i]) {
        str_cadd(&var, line->data[i]);
        i++;
    }

    return var;
}

static vec_str_t *get_arg_list(str_t *line)
{
    long start = str_find(line, STR("("), 0) + 1;
    long end = str_find(line, STR(")"), 0);

    if (start == -1 || end == -1 || start >= end)
        return NULL;

    str_t *tmp = str_substr(line, start, end - start);
    vec_str_t *list = str_split(tmp, STR(" "));
    free(tmp);
    return list;
}

int builtin_foreach(vec_str_t *av, shell_t *state)
{
    long int offset = ftell(stdin);
    str_t *tmp = str_join(av, STR(" "));
    str_t *var = get_var_name(tmp);
    vec_str_t *list = get_arg_list(tmp);
    free(tmp);
    if (list == NULL) {
        free(var);
        return 1;
    }
    if (offset == (long int)(-1))
        return piped_foreach(state, var, list);
    return script_foreach(state, var, list, offset);
}
