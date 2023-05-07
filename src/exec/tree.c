/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exec tree
*/

#include <stdio.h>
#include <stdlib.h>

#include "my_str.h"
#include "my_vec.h"

#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"

static int should_exit(shell_t *state, vec_str_t *av)
{
    if (str_eq(av->data[0], STR("exit"))) {
        state->stop_shell = 1;
        kill_children(state);
        if (av->size > 1)
            state->return_code = str_toint(av->data[1]);
        return 1;
    }
    return 0;
}

static void exec_wrapper_inner(shell_t *state, vec_str_t *av)
{
    int (*builtin)(vec_str_t *, shell_t *) = NULL;
    int is_out_pipe = !state->pipe.is_active || state->pipe.action == READ;
    str_t *alias = NULL;

    if ((builtin = map_get(state->builtins, av->data[0])) != NULL &&
        is_out_pipe) {
        state->return_code = builtin(av, state);
        vec_free(av);
        return;
    }
    if ((alias = map_get(state->alias, av->data[0])) != NULL) {
        vec_free(av);
        av = parse_args(state, alias->data);
    }
    exec_command(state, builtin, av);
    vec_free(av);
}

void exec_wrapper(shell_t *state, char const *line)
{
    vec_str_t *av = parse_args(state, line);

    if (av == NULL) {
        state->return_code = 1;
        return;
    }
    if (av->size == 0 || should_exit(state, av)) {
        return;
    }
    exec_wrapper_inner(state, av);
}

void exec_tree(shell_t *state, bnode_t *node)
{
    if (state->stop_cmd)
        return;
    if (is_symbol(node->data)) {
        str_t *key = str_create(node->data);
        middleware_t cb = map_get(state->middlewares, key);
        cb(state, node);
        free(key);
        return;
    }
    if (!IS_END(node)) {
        exec_tree(state, node->left);
        exec_tree(state, node->right);
        return;
    }
    exec_wrapper(state, node->data);
}
