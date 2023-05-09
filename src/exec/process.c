/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** process manager
*/

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"

void kill_children(shell_t *state)
{
    vec_pid_t *pids = state->jobs;

    for (size_t i = 0; i < pids->size; ++i) {
        kill(pids->data[i], SIGKILL);
    }
}

void waitpid_for_process(shell_t *state, pid_t pid, int *code)
{
    waitpid(pid, code, WUNTRACED);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, state->shell_pgid);
    signal(SIGTTOU, SIG_DFL);
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
        waitpid_for_process(state, pid, &code);
        exec_error(code);
        state->return_code = WEXITSTATUS(code);
    }
    print_job_status(code, pid);
}
