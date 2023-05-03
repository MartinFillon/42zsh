/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** question_mark_handler
*/

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_str.h"
#include "my_vec.h"

static int is_matching(char const *word, char const *entry)
{
    if (strlen(word) != strlen(entry))
        return 0;

    for (size_t i = 0; word[i] != '\0'; i++) {
        if (word[i] == '?')
            continue;
        if (word[i] != entry[i])
            return 0;
    }
    return 1;
}

static DIR *open_directory(str_t const *word)
{
    str_t *tmp = NULL;
    DIR *dir = NULL;
    long last_slash = str_findlast(word, STR("/"));

    if (last_slash == -1)
        return opendir(".");
    if (last_slash == 0)
        return opendir("/");
    tmp = str_create(str_startswith(word, STR("/")) ? "/" : "./");
    str_nadd(&tmp, word->data, last_slash);
    dir = opendir(str_tocstr(tmp));
    free(tmp);
    return dir;
}

static str_t *get_pattern(str_t const *word)
{
    long last_slash = str_findlast(word, STR("/"));

    if (last_slash == -1)
        return str_dup(word);

    return str_substr(word, last_slash + 1, word->length - last_slash);
}

static vec_str_t *get_entries(DIR *dir, str_t const *pattern)
{
    vec_str_t *vec = vec_create(100, sizeof(str_t *));

    for (struct dirent *e = readdir(dir); e != NULL; e = readdir(dir))
        if (is_matching(str_tocstr(pattern), e->d_name))
            vec_pushback(&vec, &(str_t *){str_create(e->d_name)});

    closedir(dir);
    return vec;
}

vec_str_t *question_mark_handler(str_t *word)
{
    DIR *dir = open_directory(word);
    str_t *pattern = get_pattern(word);

    if (!dir) {
        dprintf(2, "Open failed.\n");
        return NULL;
    }
    if (!pattern) {
        dprintf(2, "Pattern failed.\n");
        return NULL;
    }
    return get_entries(dir, pattern);
}
