/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** process manager
*/

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "my_str.h"

void kill_children(shell_t *state)
{
    vec_pid_t *pids = state->jobs;

    for (size_t i = 0; i < pids->size; ++i) {
        kill(pids->data[i], SIGKILL);
    }
}

void print_job_status(int code, pid_t pid)
{
    if (WIFSTOPPED(code)) {
        fprintf(stderr, "\n[%d] Stopped\n", pid);
    }
}

long find_job_by_pid(shell_t *state, pid_t pid)
{
    for (size_t i = 0; i < state->jobs->size; ++i)
        if (state->jobs->data[i] == pid)
            return i;

    return -1;
}

void remove_zombies(shell_t *state)
{
    int status = 0;
    pid_t pid = 0;
    long job_idx = 0;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        if (!WIFEXITED(status))
            continue;

        job_idx = find_job_by_pid(state, pid);

        if (job_idx != -1)
            vec_remove(state->jobs, job_idx);
    }
}

void wait_for_process(shell_t *state, pid_t pid)
{
    int code = 0;

    setpgid(pid, state->cmd_pgid);
    if (!state->exec_cmd_in_bg)
        tcsetpgrp(STDIN_FILENO, state->cmd_pgid);
    vec_pushback(&state->jobs, &pid);
    if (state->redirect.is_active)
        redirect_reset(&state->redirect);
    if (state->pipe.is_active) {
        if (state->pipe.first_pid == -1)
            state->pipe.first_pid = pid;
        return;
    }
    if (!state->exec_cmd_in_bg) {
        waitpid(pid, &code, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, state->shell_pgid);
        exec_error(code);
        state->return_code = WEXITSTATUS(code);
    }
    print_job_status(code, pid);
}
