/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** sub commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "my_btree.h"
#include "my_str.h"
#include "my_utils.h"

static void read_output(str_t **out, int fd)
{
    char c = 0;

    while (read(fd, &c, 1) > 0)
        str_cadd(out, c);
}

static void exec_sub_proc(shell_t *state, str_t *sub_cmd, str_t **out)
{
    int p[2];
    int stdout = dup(STDOUT_FILENO);

    if (pipe(p) < 0) {
        perror("pipe");
        exit(1);
    }
    dup2(p[1], STDOUT_FILENO);
    btree_t *tree = gen_exec_tree(sub_cmd->data);
    exec_tree(state, tree->root);
    btree_free(tree);
    close(STDOUT_FILENO);
    close(p[1]);
    read_output(out, p[0]);
    close(p[0]);
    dup2(stdout, STDOUT_FILENO);
    free(sub_cmd);
}

str_t *exec_backticks(shell_t *state, str_t *line)
{
    str_t *line_ = str_screate(line->length);
    long _btick = -1;

    for (size_t i = 0; i < line->length; ++i) {
        if (i > 0 && line->data[i - 1] == '\\') {
            str_cadd(&line_, line->data[i]);
            continue;
        }
        if (_btick == -1 && line->data[i] == '`') {
            _btick = i + 1;
            continue;
        }
        if (_btick == -1) str_cadd(&line_, line->data[i]);
        if (line->data[i] == '`') {
            exec_sub_proc(state, str_substr(line, _btick, i - _btick), &line_);
            _btick = -1;
        }
    }
    free(line);
    return line_;
}
