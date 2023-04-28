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
    struct dirent *dir_entry = NULL;
    str_t *tmp;

    if (dir == NULL)
        return;
    dir_entry = readdir(dir);
    for (; dir_entry != NULL; dir_entry = readdir(dir)) {
        if (dir_entry->d_name[0] == '.')
            continue;
        tmp = str_dup(path);
        if (tmp->data[tmp->length - 1] != '/')
            str_cadd(&tmp, '/');
        str_add(&tmp, dir_entry->d_name);
        if (str_endswith(tmp, pattern)) {
            vec_pushback(&matches, &tmp);
        }
    }
}

vec_str_t *get_wildcard_matches(str_t *pattern)
{
    vec_str_t *matches = vec_create(100, sizeof(str_t *));
    vec_str_t *pattern_parts = str_split(pattern, STR("*"));
    DIR *dir = NULL;

    if (str_startswith(pattern_parts->data[0], STR("/"))
        || str_startswith(pattern_parts->data[0], STR("./")))
        dir = opendir(str_tocstr(pattern_parts->data[0]));
    else
        dir = opendir(".");
    get_entrys(matches, dir, pattern_parts->data[1], pattern_parts->data[0]);
    return matches;
}
