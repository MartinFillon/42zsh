/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** args
*/

#include <stdlib.h>

#include "my_map.h"
#include "my_str.h"
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

vec_str_t *parse_args(shell_t *state, char const *line)
{
    str_t *line_ = parse_variables(line, state);

    if (line_ == NULL)
        return NULL;

    vec_str_t *args_ = str_split(line_, STR(" \t"));
    vec_str_t *args = (vec_str_t *)vec_filter(args_, &keep_arg_or_free);

    if (args->size > 1 && str_eq(VEC_LAST(args), STR("&"))) {
        state->exec_cmd_in_bg = 1;
        free(VEC_LAST(args));
        vec_popback(args);
    }
    free(line_);
    free(args_);
    return args;
}
