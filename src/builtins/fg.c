/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** fg
*/

#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

#include "mysh/exec.h"

static pid_t find_latest_process(shell_t *state)
{
    while (state->jobs->size > 0) {
        if (kill(-VEC_LAST(state->jobs), SIGCONT) < 0) {
            vec_popback(state->jobs);
        } else {
            return VEC_LAST(state->jobs);
        }
    }

    dprintf(2, "fg: no current job\n");
    return -1;
}

int builtin_fg(vec_str_t *av, shell_t *state)
{
    pid_t pid = -1;
    int code = 0;

    if (av->size > 1) {
        pid = str_toint(av->data[1]);
        if (kill(-pid, SIGCONT) < 0) {
            dprintf(2, "fg: %d: no such job\n", pid);
            return 1;
        }
    } else {
        if ((pid = find_latest_process(state)) == -1)
            return 1;
    }
    tcsetpgrp(STDIN_FILENO, pid);
    waitpid_for_process(state, pid, &code);
    print_job_status(code, pid);
    return 0;
}
