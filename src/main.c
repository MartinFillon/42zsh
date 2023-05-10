/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** mysh main entry
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include "my_btree.h"
#include "my_map.h"
#include "my_utils.h"
#include "my_vec.h"

#include "mysh/builtins.h"
#include "mysh/exec.h"
#include "mysh/history.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"
#include "mysh/read.h"

static void read_rc(shell_t *state)
{
    FILE *fd = fopen(".42zshrc", "r");
    char *line = NULL;
    size_t len = 0;

    if (fd == NULL)
        return;
    while (getline(&line, &len, fd) != -1) {
        if (line[0] == '\n')
            continue;
        line[strlen(line) - 1] = '\0';
        parse_input(state, line);
    }
    fclose(fd);
    return;
}

static void state_free(shell_t *state)
{
    map_free(state->middlewares, NULL);
    map_free(state->builtins, NULL);
    map_free(state->env, &free);
    pipe_close(&state->pipe);
    map_free(state->alias, &free);
    map_free(state->vars, &free);
    free(state->jobs);
    history_free(&state->history);
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
    state->jobs = vec_create(100, sizeof(job_t));
    state->alias = map_create(1000);
    state->history = history_create();

    catch_signals();
    read_rc(state);
    if (state->is_atty) {
        setpgid(state->shell_pgid, state->shell_pgid);
        tcsetpgrp(STDIN_FILENO, state->shell_pgid);
    }
}

void handle_shebang(int ac, char **av)
{
    int fd = 0;
    char *line = NULL;
    size_t len = 0;

    if (ac != 2)
        return;
    if (access(av[1], F_OK) == 0) {
        fd = open(av[1], O_RDONLY);
        dup2(fd, 0);
        getline(&line, &len, stdin);
        return;
    }
}

int main(int ac, char **av, char const *const *envp)
{
    shell_t state = {0};

    handle_shebang(ac, av);
    init_shell(&state, envp);
    read_input(&state);
    state_free(&state);
    return state.return_code;
}
