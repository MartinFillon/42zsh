/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** wildcard_handler
*/

#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "my_str.h"
#include "my_vec.h"

void get_entrys(vec_str_t *matches, DIR *dir, str_t *pattern, str_t *path)
{
    str_t *tmp;

    for (struct dirent *d = readdir(dir); d != NULL; d = readdir(dir)) {
        tmp = str_dup(path);
        if (tmp->data[tmp->length - 1] != '/')
            str_cadd(&tmp, '/');
        str_add(&tmp, d->d_name);
        if (str_endswith(tmp, pattern)) {
            vec_pushback(&matches, &tmp);
        }
    }
}

vec_str_t *get_wildcard_matches(str_t *pattern)
{
    vec_str_t *matches = vec_create(100, sizeof(str_t *));
    vec_str_t *pattern_parts = str_split(pattern, STR("*"));
    DIR *dir = (str_startswith(pattern_parts->data[0], STR("/")) ||
        str_startswith(pattern_parts->data[0], STR("./")))
        ? opendir(str_tocstr(pattern_parts->data[0]))
        : opendir(".");

    get_entrys(matches, dir, pattern_parts->data[1], pattern_parts->data[0]);
    return matches;
}
