/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** process manager
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"

void kill_children(shell_t *state)
{
    vec_job_t *pids = state->jobs;

    for (size_t i = 0; i < pids->size; ++i) {
        kill(pids->data[i].pgid, SIGKILL);
    }
}

void waitpid_for_process(shell_t *state, pid_t pid, int *code)
{
    waitpid(pid, code, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, state->shell_pgid);

    if (WIFEXITED(*code) || WIFSIGNALED(*code)) {
        long job_idx = find_job_by_pid(state, pid);
        free(state->jobs->data[job_idx].cmd);
        vec_remove(state->jobs, job_idx);
    }
}

void wait_for_process(shell_t *state, pid_t pid)
{
    int code = 0;

    setpgid(pid, state->cmd_pgid);
    if (!state->exec_cmd_in_bg)
        tcsetpgrp(STDIN_FILENO, state->cmd_pgid);
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
