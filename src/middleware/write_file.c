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
    r->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    r->action = APPEND;
    if (r->fd == -1) {
        dprintf(2, "%s: %s.\n", file, strerror(errno));
        return 1;
    }
    return 0;
}

void write_file_middleware(shell_t *state, bnode_t *node)
{
    redirect_t *r = state->redirect;
    char *file = NULL;

    if (!IS_END(node->right) || r->is_active) {
        dprintf(2, "Ambiguous output redirect.\n");
        return;
    }
    file = trim_string(node->right->data);
    if (setup_redirect(r, file) != 0)
        return;
    exec_tree(state, node->left);
    r->is_active = 0;
    free(file);
}
