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
#include "my_str.h"
#include "my_utils.h"

static void read_output(str_t **out, int fd)
{
    char c = 0;

    while (read(fd, &c, 1) > 0)
        str_cadd(out, c);
}

static void exec_sub_cmd(shell_t *state, str_t *sub_cmd, str_t **out)
{
    int p[2];
    int stdout = dup(STDOUT_FILENO);

    if (pipe(p) < 0) {
        perror("pipe");
        exit(1);
    }
    dup2(p[1], STDOUT_FILENO);
    exec_wrapper(state, sub_cmd->data);
    close(STDOUT_FILENO);
    close(p[1]);
    read_output(out, p[0]);
    close(p[0]);
    dup2(stdout, STDOUT_FILENO);
}

str_t *exec_sub_cmds(shell_t *state, str_t *line)
{
    str_t *line_ = str_screate(line->length);
    long _btick = -1;

    for (size_t i = 0; i < line->length; ++i) {
        if (i > 0 && line->data[i - 1] == '\\') {
            str_cadd(&line_, line->data[i]);
            continue;
        }
        if (_btick == -1 && line->data[i] == '`')
            _btick = i + 1;
        if (_btick == -1)
            str_cadd(&line_, line->data[i]);
        if (_btick != -1 && line->data[i] == '`') {
            exec_sub_cmd(state, str_substr(line, _btick, i - _btick), &line_);
            _btick = -1;
        }
    }
    free(line);
    return line_;
}
