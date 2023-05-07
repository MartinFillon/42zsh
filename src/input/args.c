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

static int keep_arg_or_free(void *ptr)
{
    str_t *arg = *(str_t **)ptr;

    if (arg->length > 0) {
        return 1;
    } else {
        free(arg);
        return 0;
    }
}

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
    vec_str_t *split_ = str_split(line_, STR(" \t"));
    vec_str_t *args_ = (vec_str_t *)vec_filter(split_, &keep_arg_or_free);
    vec_str_t *args = get_globbings(args_);
    if (args == NULL) {
        dprintf(2, "%s: No match.\n", args_->data[0]->data);
        vec_free(args_);
        my_vfree(2, line_, split_);
        return NULL;
    }
    check_exec_job_in_bg(state, args);
    my_vfree(3, line_, split_, args_);
    return args;
}
