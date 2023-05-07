/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>

#include "my_map.h"

#include "mysh/history.h"
#include "mysh/mysh.h"

void save_history(history_t *history)
{
    FILE *fp = fopen(history->destination->data, "w+");

    if (fp == NULL)
        return;

    for (size_t i = 0; i < history->entries->size; i++) {
        fprintf(fp, "#+%ld\n", history->entries->data[i].timestamp);
        fprintf(fp, "%s\n", history->entries->data[i].command->data);
    }
    fclose(fp);
}

void history_append(char *input, history_t *history)
{
    time_t now = time(NULL);
    history_entry_t entry;

    entry.command = str_create(input);
    entry.timestamp = now;
    vec_pushback(&history->entries, &entry);
}

void history_free(history_t *history)
{
    for (size_t i = 0; i < history->entries->size; i++) {
        free(history->entries->data[i].command);
    }
    free(history->entries);
    free(history->destination);
}

history_t history_create(void)
{
    static char PATHNAME[MAXPATHLEN] = "";
    char *cwd = getcwd(PATHNAME, MAXPATHLEN);
    history_t history = {
        .entries = vec_create(100, sizeof(history_entry_t)),
        .destination = str_create(cwd),
    };

    str_add(&history.destination, "/.42sh_history");
    return history;
}
