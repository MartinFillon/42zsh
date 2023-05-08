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

static void exec_sub_proc(shell_t *state, str_t *sub_cmd)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        btree_t *tree = gen_exec_tree(sub_cmd->data);
        exec_tree(state, tree->root);
        btree_free(tree);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    free(sub_cmd);
}

str_t *exec_sub_shell(shell_t *state, str_t *line)
{
    str_t *line_ = str_screate(line->length);
    long _par = -1;

    for (size_t i = 0; i < line->length; ++i) {
        if (i > 0 && line->data[i - 1] == '\\') {
            str_cadd(&line_, line->data[i]);
            continue;
        }
        if (_par == -1 && line->data[i] == '(') {
            _par = i + 1;
            continue;
        }
        if (_par == -1) str_cadd(&line_, line->data[i]);
        if (line->data[i] == ')') {
            exec_sub_proc(state, str_substr(line, _par, i - _par));
            _par = -1;
        }
    }
    free(line);
    return line_;
}
