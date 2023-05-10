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
#include "my_cstr.h"
#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/mysh.h"

static void read_and_send_input(int fd, char *stop)
{
    char *line = NULL;
    size_t l_cap = 0;
    ssize_t l_size = 0;

    while (1) {
        write(1, "? ", 2);
        l_size = getline(&line, &l_cap, stdin);

        if (l_size <= 0 || strncmp(line, stop, l_size - 1) == 0)
            break;

        write(fd, line, strlen(line));
    }
    free(line);
}

void heredoc_middleware(shell_t *state, bnode_t *node)
{
    int fds[2];
    redirect_t *r = &state->redirect;
    char *end = trim_string(node->right->data);

    if (pipe(fds) < 0)
        exit(1);

    r->is_active = 1;
    r->fd = fds[0];
    r->action = READ;
    read_and_send_input(fds[1], end);
    close(fds[1]);
    exec_tree(state, node->left);
    close(fds[0]);
    free(end);
}
