/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** globbings
*/

#include <errno.h>
#include <glob.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_str.h"
#include "my_vec.h"

#include "mysh/read.h"

vec_str_t *get_matches(str_t *pattern)
{
    vec_str_t *get_matches = vec_create(100, sizeof(str_t *));
    glob_t res;

    res.gl_offs = 0;
    glob(pattern->data, GLOB_TILDE, NULL, &res);
    for (size_t i = 0; i < res.gl_pathc; i++) {
        vec_pushback(&get_matches, &(str_t *){str_create(res.gl_pathv[i])});
    }
    globfree(&res);
    free(pattern);
    return get_matches;
}

static int is_globeable(str_t *arg)
{
    if ((str_startswith(arg, STR("'")) && str_endswith(arg, STR("'"))) ||
        (str_startswith(arg, STR("\"")) && str_endswith(arg, STR("\""))))
        return 0;
    return (
        str_contains(arg, '*') || str_contains(arg, '?') ||
        (str_contains(arg, '[') && str_contains(arg, ']'))
    );
}

static vec_str_t *error_wrapper(
    bool has_matched, vec_str_t *tmp, vec_str_t *args, vec_str_t *new_args
)
{
    if (has_matched || tmp == NULL) {
        free(args);
        return new_args;
    } else {
        dprintf(2, "%s: No match.\n", str_tocstr(args->data[0]));
        free(args);
        vec_free(new_args);
        return NULL;
    }
}

vec_str_t *get_globbings(vec_str_t *args)
{
    vec_str_t *new_args = vec_create(args->size, sizeof(str_t *));
    vec_str_t *tmp = NULL;
    bool has_matched = false;

    for (size_t i = 0; i < args->size; i++) {
        int can_glob = is_globeable(args->data[i]);
        remove_escaped_chars_and_quotes(args->data[i]);
        if (can_glob) {
            tmp = get_matches(args->data[i]);
            vec_merge(&new_args, tmp);
            has_matched |= (tmp->size > 0);
            free(tmp);
        } else
            vec_pushback(&new_args, &args->data[i]);
    }
    return error_wrapper(has_matched, tmp, args, new_args);
}
