/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** mysh main entry
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "my_btree.h"
#include "my_map.h"
#include "my_utils.h"
#include "my_vec.h"

#include "mysh/builtins.h"
#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"
#include "mysh/read.h"

static void state_free(shell_t *state)
{
    map_free(state->middlewares, NULL);
    map_free(state->builtins, NULL);
    map_free(state->env, &free);
    pipe_close(&state->pipe);
    free(state->jobs);
    map_free(state->vars, &free);
}

static void init_shell(shell_t *state, char const *const *envp)
{
    state->env = env_create(envp);
    state->builtins = builtins_create();
    state->middlewares = middleware_create();
    state->is_atty = isatty(STDIN_FILENO);
    state->shell_pgid = getpid();
    state->cmd_pgid = -1;
    state->redirect = redirect_create();
    state->pipe = pipe_create();
    state->vars = vars_create(state->env);
    state->jobs = vec_create(100, sizeof(pid_t));
    if (state->is_atty) {
        setpgid(state->shell_pgid, state->shell_pgid);
        tcsetpgrp(STDIN_FILENO, state->shell_pgid);
    }
}

int main(int UNUSED ac, char UNUSED **av, char const *const *envp)
{
    shell_t state = {0};

    init_shell(&state, envp);
    catch_signals();
    read_input(&state);
    state_free(&state);
    return state.return_code;
}
