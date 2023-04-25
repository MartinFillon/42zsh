/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** question_mark_handler
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "my_str.h"
#include "my_vec.h"

static int is_matching(char *word, char *entry)
{
    int i = 0;

    if (strlen(word) != strlen(entry))
        return (0);
    for (i = 0; word[i] != '\0'; i++) {
        if (word[i] == '?')
            continue;
        if (word[i] != entry[i])
            return (0);
    }
    return (1);
}

static DIR *open_directory(str_t *word)
{
    long index = 0;
    long last_slash = 0;
    str_t *tmp;
    DIR *dir = NULL;

    if (!str_contains(word, '/')) {
        free(word);
        return (opendir("."));
    }
    while (index != -1) {
        last_slash = index;
        index = str_find(word, STR("/"), index + 1);
    }
    tmp = str_create("./");
    tmp = *str_add(&tmp, str_tocstr(str_substr(word, 0, last_slash)));
    dir = (opendir(str_tocstr(tmp)));
    perror(str_tocstr(tmp));
    free(word);
    free(tmp);
    return (dir);
}

static str_t *get_pattern(str_t *word)
{
    long index = 0;
    long last_slash = 0;
    str_t *tmp;
    str_t *pattern;

    if (!str_contains(word, '/'))
        return (word);
    while (index != -1) {
        last_slash = index;
        index = str_find(word, STR("/"), index + 1);
    }
    tmp = str_substr(word, last_slash + 1, word->length - last_slash);
    pattern = str_create(str_tocstr(tmp));
    free(word);
    free(tmp);
    return (pattern);
}

static vec_str_t *get_entrys(DIR *dir, str_t *pattern)
{
    struct dirent *entry = NULL;
    vec_str_t *vec = vec_create(100, sizeof(str_t *));
    str_t *tmp = NULL;

    entry = readdir(dir);
    while (entry != NULL) {
        if (is_matching(str_tocstr(pattern), entry->d_name)) {
            tmp = str_create(entry->d_name);
            vec_pushback(&vec, &tmp);
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return (vec);
}

vec_str_t *question_mark_handler(str_t *word)
{
    DIR *dir = NULL;
    str_t *pattern = NULL;

    if (!str_contains(word, '?')) {
        dprintf(2, "No match possible.\n");
        return (NULL);
    }
    dir = open_directory(str_dup(word));
    pattern = get_pattern(str_dup(word));
    if (!dir) {
        dprintf(2, "Open failed.\n");
        return (NULL);
    }
    if (!pattern) {
        dprintf(2, "Pattern failed.\n");
        return (NULL);
    }
    return (get_entrys(dir, pattern));
}
