/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** which
*/

#include <stdio.h>

#include "mysh/mysh.h"
#include "my_str.h"

static int which_path(str_t *s, shell_t *state)
{
    str_t *path = map_get(state->env, STR("PATH"));
    vec_str_t *paths = NULL;

    if (path == NULL)
        return 1;
    paths = str_split(path, STR(":"));
    for (size_t i = 0; i < paths->size; i++) {
        if (paths->data[i]->data[paths->data[i]->length - 1] != '/')
            str_cadd(&paths->data[i], '/');
        str_sadd(&paths->data[i], s);
        if (access(paths->data[i]->data, F_OK) == 0) {
            printf("%s\n", paths->data[i]->data);
            return 0;
        }
    }
    return 1;
}

static int check_presence(str_t *s, shell_t *state)
{
    str_t *tmp;

    if ((tmp = map_get(state->alias, s)) != NULL) {
        tmp->data[tmp->length - 1] = (tmp->data[tmp->length - 1] == ' ')
            ? '\0'
            : tmp->data[tmp->length - 1];
        printf("%s: \t aliased to %s\n", s->data, tmp->data);
        return 0;
    }
    if ((tmp = map_get(state->builtins, s)) != NULL) {
        printf("%s: shell built-in command\n", s->data);
        return 0;
    }
    return which_path(s, state);
}

int builtin_which(vec_str_t *av, shell_t *state)
{
    int err = 0;

    for (size_t i = 1; i < av->size; i++)
        err |= check_presence(av->data[i], state);
    return (err);
}
