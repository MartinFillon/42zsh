/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** redirect
*/

#include <stdlib.h>

#include "mysh/mysh.h"

redirect_t redirect_create(void)
{
    redirect_t redirect = {
        .action = 0,
        .fd = -1,
        .is_active = 0,
    };

    return redirect;
}

void redirect_reset(redirect_t *red)
{
    if (red->fd != -1) {
        close(red->fd);
        red->fd = -1;
    }
    red->is_active = 0;
}

void redirect_apply(shell_t *state)
{
    redirect_t *r = &state->redirect;

    if (!r->is_active)
        return;
    switch (r->action) {
        case READ: dup2(r->fd, STDIN_FILENO); break;
        case WRITE:
        case APPEND: dup2(r->fd, STDOUT_FILENO); break;
    }
    if (r->fd != -1)
        close(r->fd);
}
