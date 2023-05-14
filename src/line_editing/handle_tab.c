/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** handle_tab
*/

#include <glob.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysh/mysh.h"
#include "mysh/termios.h"

static void read_for_args(shell_input_t *in)
{
    long index = str_findlast(in->input, STR(" "));
    str_t *path = str_substr(in->input, index + 1, in->input->length - index - 1);
    str_sadd(&path, STR("*"));
    glob_t globbuf;
    globbuf.gl_offs = 0;

    if (glob(path->data, 0, NULL, &globbuf) == GLOB_NOMATCH) {
        globfree(&globbuf);
        free(path);
        return;
    }
    for (size_t i = 0; i < globbuf.gl_pathc; i++) {
        printf("%s\n", globbuf.gl_pathv[i]);
    }
    globfree(&globbuf);
    free(path);
}

static void read_each_path(shell_input_t *in, str_t *path)
{
    glob_t globbuf;
    str_t *tmp = str_dup(path);

    str_sadd(&tmp, STR("/"));
    str_sadd(&tmp, in->input);
    str_sadd(&tmp, STR("*"));
    if (glob(tmp->data, 0, NULL, &globbuf) == GLOB_NOMATCH) {
        globfree(&globbuf);
        free(tmp);
        return;
    }
    for (size_t i = 0; i < globbuf.gl_pathc; i++) {
        printf("%s\n", (globbuf.gl_pathv[i] + (tmp->length - in->input->length)));
    }
    globfree(&globbuf);
    free(tmp);
}

static void read_path(shell_input_t *in, shell_t *state)
{
    str_t *path = map_get(state->env, STR("PATH"));
    vec_str_t *paths = str_split(path, STR(":"));

    for (size_t i = 0; i < paths->size; ++i) {
        read_each_path(in, paths->data[i]);
    }
    vec_free(paths);
}

void tab_show_possibilities(shell_input_t *in, shell_t *state)
{
    if (in->input->length == 0)
        return;
    printf("\n");
    if (str_contains(in->input, ' '))
        return read_for_args(in);
    return read_path(in, state);
}
