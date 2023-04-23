/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** pipe middleware
*/

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
    pipe_t *p = state->pipe;
    int code = 0;

    pipe_close(p);
    waitpid(p->pids[1], &code, 0);
    waitpid(p->pids[0], &code, 0);
    state->return_code = WEXITSTATUS(code);
    pipe_reset(p);
}

void pipe_middleware(shell_t *state, bnode_t *node)
{
    pipe_t *p = state->pipe;
    int is_piped = p->is_active;

    if (is_piped)
        pipe_chain(p);
    if (pipe(p->fds) == -1)
        exit(1);
    p->is_active = 1;
    p->action = (is_piped) ? READ_WRITE : READ;
    exec_tree(state, node->right);
    p->action = WRITE;
    exec_tree(state, node->left);
    pipe_end(state);
}
