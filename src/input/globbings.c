/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** globbings
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#include "my_str.h"
#include "my_vec.h"

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
    return get_matches;
}

vec_str_t *get_globbings(vec_str_t *args)
{
    vec_str_t *arg_cpy = vec_create(args->size, sizeof(str_t *));
    vec_str_t *tmp = NULL;

    for (size_t i = 0; i < args->size; i++) {
        if (str_contains(args->data[i], '*') ||
            str_contains(args->data[i], '?') ||
            (str_contains(args->data[i], '[') &&
             str_contains(args->data[i], ']'))) {
            tmp = get_matches(args->data[i]);
            vec_merge(&arg_cpy, tmp);
        } else {
            vec_pushback(&arg_cpy, &args->data[i]);
        }
    }
    return arg_cpy;
}
