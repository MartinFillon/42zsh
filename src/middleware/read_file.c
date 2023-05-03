/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** semicolumn
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_btree.h"

#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"

static int setup_redirect(redirect_t *r, char *file)
{
    if (strlen(file) == 0) {
        dprintf(2, "Missing name for redirect.\n");
        return 1;
    }
    r->is_active = 1;
    r->fd = open(file, O_RDONLY);
    r->action = READ;
    if (r->fd == -1) {
        dprintf(2, "%s: %s.\n", file, strerror(errno));
        return 1;
    }
    return 0;
}

void read_file_middleware(shell_t *state, bnode_t *node)
{
    redirect_t *r = state->redirect;
    char *file = NULL;

    if (state->pipe->action == READ && state->pipe->is_active) {
        dprintf(2, "Ambiguous input redirect.\n");
        return;
    }
    file = trim_string(node->right->data);
    if (setup_redirect(r, file) != 0)
        return;
    exec_tree(state, node->left);
    free(file);
}
