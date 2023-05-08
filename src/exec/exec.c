/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exec
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "my_map.h"
#include "my_str.h"
#include "my_utils.h"
#include "my_vec.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/read.h"

static const char *ERROR[] = {
    "%s: Command not found.\n",
    "%s: Permission denied.\n",
    "%s: Exec format error. Wrong Architecture.\n",
};

static void exec_from_path(vec_str_t *path, char **argv, char **envp)
{
    for (size_t i = 0; i < path->size; ++i) {
        if (!str_endswith(path->data[i], STR("/"))) {
            str_cadd(&path->data[i], '/');
        }
        str_add(&path->data[i], argv[0]);
        execve(str_tocstr(path->data[i]), argv, envp);
    }
}

static void perror_wrapper(str_t *file)
{
    switch (errno) {
        case ENOENT: dprintf(2, ERROR[0], str_tocstr(file)); break;
        case EACCES: dprintf(2, ERROR[1], str_tocstr(file)); break;
        case ENOEXEC: dprintf(2, ERROR[2], str_tocstr(file)); break;
        default: dprintf(2, "%s: %s.\n", str_tocstr(file), strerror(errno));
    }
}

static void try_exec_or_exit(
    vec_str_t *av, shell_t *state, int (*builtin)(vec_str_t *, shell_t *)
)
{
    char const *file = str_tocstr(av->data[0]);
    char **argv = arg_to_tabl(av);
    char **envp = env_to_tabl(state->env);
    vec_str_t *path = path_to_vec(state->env);

    if (builtin != NULL) {
        builtin(av, state);
        exit(1);
    }
    if (str_contains(av->data[0], '/')) {
        execve(file, argv, envp);
    } else {
        exec_from_path(path, argv, envp);
    }
    perror_wrapper(av->data[0]);
    exit(1);
}

void exec_command(
    shell_t *state, int (*builtin)(vec_str_t *, shell_t *), vec_str_t *av
)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        pipe_apply(state);
        redirect_apply(state);
        restore_signals();
        if (state->is_atty && !state->exec_cmd_in_bg) {
            state->cmd_pgid =
                (state->cmd_pgid == -1) ? getpid() : state->cmd_pgid;
            setpgid(0, state->cmd_pgid);
        }
        try_exec_or_exit(av, state, builtin);
    }
    if (state->cmd_pgid == -1)
        state->cmd_pgid = pid;
    wait_for_process(state, pid);
}
