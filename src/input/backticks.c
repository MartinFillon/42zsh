/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** sub commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "my_btree.h"
#include "my_str.h"
#include "my_utils.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"

static void read_output(str_t **out, int fd)
{
    char c;

    while (read(fd, &c, 1) > 0)
        str_cadd(out, c);
}

static void exec_sub_proc(shell_t *state, str_t *sub_cmd, int p[2])
{
    dup2(p[1], STDOUT_FILENO);
    btree_t *tree = gen_exec_tree(sub_cmd->data);
    exec_tree(state, tree->root);
    btree_free(tree);
    close(p[0]);
    close(p[1]);
}

static void get_proc_output(shell_t *state, str_t *sub_cmd, str_t **out)
{
    int p[2];
    if (pipe(p) < 0)
        exit(1);
    pid_t pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0) {
        exec_sub_proc(state, sub_cmd, p);
        exit(0);
    }
    close(p[1]);
    read_output(out, p[0]);
    waitpid(pid, NULL, 0);
    close(p[0]);
    free(sub_cmd);
}

str_t *exec_backticks(shell_t *state, str_t *line)
{
    str_t *line_ = str_screate(line->length);
    long _bt = -1;

    for (size_t i = 0; i < line->length; ++i) {
        if (i > 0 && line->data[i - 1] == '\\') {
            str_cadd(&line_, line->data[i]);
            continue;
        }
        if (_bt == -1 && line->data[i] == '`') {
            _bt = i + 1;
            continue;
        }
        if (_bt == -1) str_cadd(&line_, line->data[i]);
        if (line->data[i] == '`') {
            get_proc_output(state, str_substr(line, _bt, i - _bt), &line_);
            _bt = -1;
        }
    }
    free(line);
    return line_;
}
