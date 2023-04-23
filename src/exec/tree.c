/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exec tree
*/

#include <stdlib.h>

#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"

static int should_exit(shell_t *state, vec_str_t *av)
{
    if (str_eq(av->data[0], STR("exit"))) {
        state->stop = 1;
        if (av->size > 1) {
            state->return_code = str_toint(av->data[1]);
        }
        return 1;
    }
    return 0;
}

static void exec_wrapper(shell_t *state, vec_str_t *av)
{
    int (*builtin)(vec_str_t *av, map_t *env) = NULL;
    int is_out_pipe = !state->pipe->is_active || state->pipe->action == READ;

    if (av->size == 0 || should_exit(state, av))
        return;

    if ((builtin = map_get(state->builtins, av->data[0])) != NULL &&
        is_out_pipe) {
        state->return_code = builtin(av, state->env);
    } else {
        exec_command(state, builtin, av);
    }
}

void exec_tree(shell_t *state, bnode_t *node)
{
    vec_str_t *av = NULL;

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
    if ((av = parse_args(state->env, node->data)) == NULL) {
        state->return_code = 1;
        return;
    }
    exec_wrapper(state, av);
    vec_free(av);
}
