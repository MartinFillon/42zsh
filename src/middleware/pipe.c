/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** pipe middleware
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "my_btree.h"
#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"

static void pipe_end(shell_t *state)
{
    pipe_t *p = &state->pipe;
    int code = 0;

    pipe_close(p);
    waitpid(p->first_pid, &code, WUNTRACED);
    if (!state->exec_cmd_in_bg)
        tcsetpgrp(STDIN_FILENO, state->shell_pgid);
    state->return_code = WEXITSTATUS(code);
    print_job_status(code, p->first_pid);
    pipe_reset(p);
}

static int is_invalid_pipe(char const *str)
{
    int error = 0;
    str_t *temp;

    if (str == NULL)
        return 1;

    temp = str_create(str);
    str_trim(&temp, ' ');
    str_trim(&temp, '\t');
    error = temp->length == 0;
    free(temp);
    return error;
}

void pipe_middleware(shell_t *state, bnode_t *node)
{
    pipe_t *p = &state->pipe;
    int is_piped = p->is_active;

    if (is_invalid_pipe(node->left->data) ||
        is_invalid_pipe(node->right->data)) {
        dprintf(2, "Invalid null command.\n");
        state->stop_cmd |= !is_piped;
        return;
    }
    if (is_piped)
        pipe_chain(p);
    if (pipe(p->fds) == -1)
        exit(1);
    p->is_active = 1;
    p->action = (is_piped) ? READ_WRITE : READ;
    exec_tree(state, node->right);
    p->action = WRITE;
    exec_tree(state, node->left);
    if (!is_piped)
        pipe_end(state);
}
