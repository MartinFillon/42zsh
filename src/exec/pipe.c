/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** pipe
*/

#include <stdlib.h>

#include "my_btree.h"
#include "my_vec.h"

#include "mysh/mysh.h"

pipe_t *pipe_create(void)
{
    pipe_t *pipe_ctx = malloc(sizeof(pipe_t));

    pipe_ctx->action = READ;
    pipe_ctx->is_active = 0;
    pipe_ctx->fds[0] = -1;
    pipe_ctx->fds[1] = -1;
    pipe_ctx->pipe_fd = -1;
    pipe_ctx->pids[0] = -1;
    pipe_ctx->pids[1] = -1;

    return pipe_ctx;
}

void pipe_close(pipe_t *pipe)
{
    if (pipe->fds[0] != -1) {
        close(pipe->fds[0]);
        pipe->fds[0] = -1;
    }
    if (pipe->fds[1] != -1) {
        close(pipe->fds[1]);
        pipe->fds[1] = -1;
    }
    if (pipe->pipe_fd != -1) {
        close(pipe->pipe_fd);
        pipe->pipe_fd = -1;
    }
}

void pipe_chain(pipe_t *pipe)
{
    if (pipe->pipe_fd != -1) {
        close(pipe->pipe_fd);
        pipe->pipe_fd = -1;
    }
    pipe->pipe_fd = pipe->fds[1];
    if (pipe->fds[0] != -1) {
        close(pipe->fds[0]);
        pipe->fds[0] = -1;
    }
}

void pipe_apply(shell_t *state)
{
    pipe_t *p = state->pipe;
    if (!p->is_active)
        return;

    switch (p->action) {
    case READ:
        dup2(p->fds[0], STDIN_FILENO);
        break;
    case WRITE:
        dup2(p->fds[1], STDOUT_FILENO);
        break;
    case READ_WRITE:
        dup2(p->fds[0], STDIN_FILENO);
        dup2(p->pipe_fd, STDOUT_FILENO);
        break;
    }
    pipe_close(p);
}

void pipe_reset(pipe_t *p)
{
    p->is_active = 0;
    p->fds[0] = -1;
    p->fds[1] = -1;
    p->pipe_fd = -1;
    p->pids[0] = -1;
    p->pids[1] = -1;
}
