/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** jobs utils
*/

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"

void print_job_status(int code, pid_t pid)
{
    if (WIFSTOPPED(code)) {
        dprintf(2, "\n[%d] Stopped\n", pid);
    }
}

long find_job_by_pid(shell_t *state, pid_t pid)
{
    for (size_t i = 0; i < state->jobs->size; ++i)
        if (state->jobs->data[i].pgid == pid)
            return i;

    return -1;
}

void remove_zombies(shell_t *state)
{
    int status = 0;
    pid_t pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
    long job_idx = 0;

    while (pid >= 0) {
        if (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
            continue;
        }

        job_idx = find_job_by_pid(state, pid);

        if (job_idx != -1) {
            free(state->jobs->data[job_idx].cmd);
            vec_remove(state->jobs, job_idx);
        }
        pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
    }
}
