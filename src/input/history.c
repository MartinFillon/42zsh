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


static void load_history(history_t *history)
{
    char *buffer = open_file(history->destination->data);
    vec_str_t *lines = NULL;
    history_entry_t entry;
    str_t *tmp = NULL;

    if (buffer == NULL){
        return;
    }
    lines = str_split(str_create(buffer), STR("\n"));
    for (size_t i = 0;i < lines->size;i++){
        if (str_startswith(lines->data[i], STR("#+")) == 1){
            tmp = str_create(lines->data[i]->data);
            str_slice(&tmp, 2, lines->data[i]->length);
            entry.timestamp = atof(tmp->data);
            entry.command = lines->data[i + 1];
            vec_pushback(&history->entries, &entry);
        }
    }
}

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
    history_entry_t entry = {now, str_create(input)};

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

    str_add(&history.destination, "/.42zsh_history");
    load_history(&history);
    return history;
}
