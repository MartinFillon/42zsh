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

void append_file_middleware(shell_t *state, bnode_t *node)
{
    redirect_t *r = state->redirect;
    char *file = NULL;

    if (!IS_END(node->right)) {
        dprintf(2, "Ambiguous output redirect.\n");
        return;
    }
    file = trim_string(node->right->data);
    r->is_active = 1;
    r->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    r->action = APPEND;
    if (r->fd == -1) {
        dprintf(2, "Failed to open file: %s\n", file);
        return;
    }
    exec_tree(state, node->left);
    free(file);
}
