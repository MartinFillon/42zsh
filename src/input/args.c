/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** args
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_map.h"
#include "my_str.h"
#include "my_utils.h"
#include "my_vec.h"

#include "mysh/mysh.h"
#include "mysh/read.h"

static void check_exec_job_in_bg(shell_t *state, vec_str_t *args)
{
    if (args->size > 1 && str_eq(VEC_LAST(args), STR("&"))) {
        state->exec_cmd_in_bg = 1;
        free(VEC_LAST(args));
        vec_popback(args);
    }
}

vec_str_t *parse_args(shell_t *state, char const *line)
{
    str_t *line_ = parse_variables(line, state);
    if (line_ == NULL)
        return NULL;

    line_ = exec_sub_cmds(state, line_);
    vec_str_t *args_ = split_args(line_);
    if (args_ == NULL)
        return NULL;

    vec_str_t *args = get_globbings(args_);
    if (args == NULL)
        return NULL;

    check_exec_job_in_bg(state, args);
    return args;
}
