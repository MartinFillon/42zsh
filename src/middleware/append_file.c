/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** semicolumn
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_btree.h"
#include "my_str.h"

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
    r->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    r->action = APPEND;
    if (r->fd == -1) {
        dprintf(2, "Failed to open file: %s\n", file);
        return 1;
    }
    return 0;
}

void append_file_middleware(shell_t *state, bnode_t *node)
{
    redirect_t *r = &state->redirect;
    char *file = NULL;

    if (!IS_END(node->right)) {
        dprintf(2, "Ambiguous output redirect.\n");
        state->return_code = 1;
        return;
    }
    file = trim_string(node->right->data);
    if (setup_redirect(r, file) != 0) {
        state->return_code = 1;
        return;
    }
    exec_tree(state, node->left);
    free(file);
}
