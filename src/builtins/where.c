/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** where
*/

#include <stddef.h>
#include <stdio.h>
#include "mysh/mysh.h"
#include "my_str.h"

static int is_in_path(str_t *s, shell_t *state)
{
    str_t *path = map_get(state->env, STR("PATH"));
    vec_str_t *paths = NULL;
    int err = 0;

    if (path == NULL)
        return 1;
    paths = str_split(path, STR(":"));
    for (size_t i = 0; i < paths->size; i++) {
        if (paths->data[i]->data[paths->data[i]->length - 1] != '/')
            str_cadd(&paths->data[i], '/');
        str_sadd(&paths->data[i], s);
        if (access(paths->data[i]->data, F_OK) == 0) {
            printf("%s\n", paths->data[i]->data);
            err |= 1;
        }
    }
    vec_free(paths);
    return err;
}

static int check_presence(str_t *s, shell_t *state)
{
    str_t *tmp;
    int err = 0;

    if ((tmp = map_get(state->alias, s)) != NULL) {
        printf("%s is aliased to %s\n", s->data, tmp->data);
        err |= 1;
    }
    if ((tmp = map_get(state->builtins, s)) != NULL) {
        printf("%s is a shell built-in\n", s->data);
        err |= 1;
    }
    err |= is_in_path(s, state);
    return (!err);
}

int builtin_where(vec_str_t *av, shell_t *state)
{
    int err = 0;

    if (av->size == 1) {
        dprintf(2, "where: Too few arguments.\n");
        return (1);
    }
    for (size_t i = 1; i < av->size; i++) {
        err |= check_presence(av->data[i], state);
    }
    return (err);
}
