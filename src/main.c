/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** mysh main entry
*/

#include <stdlib.h>

#include "my_btree.h"
#include "my_map.h"
#include "my_utils.h"
#include "my_vec.h"

#include "mysh/builtins.h"
#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"
#include "mysh/history.h"
#include "mysh/read.h"

static void state_free(shell_t *state)
{
    map_free(state->middlewares, NULL);
    map_free(state->builtins,NULL);
    map_free(state->env, &free);
    pipe_close(state->pipe);
    free(state->pipe);
    free(state->redirect);
    map_free(state->vars, &free);
}

int main(int UNUSED ac, char UNUSED **av, char **envp)
{
    shell_t state = {
        .return_code = 0,
        .stop_shell = 0,
        .stop_command = 0,
        .middlewares = middleware_create(),
        .redirect = redirect_create(),
        .builtins = builtins_create(),
        .env = env_create(envp),
        .is_atty = isatty(STDIN_FILENO),
        .pipe = pipe_create(),
        .vars = vars_create(state.env),
    };

    catch_signals();
    read_input(&state);
    state_free(&state);
    return state.return_code;
}
