/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>

#include "my_map.h"
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
    free(history->destination);
}

void history_append(char *input, history_t *history)
{
    time_t now = time(NULL);
    history_entry_t entry;

    entry.command = str_create(input);
    entry.timestamp = now;
    vec_pushback(&history->entries, &entry);
}

history_t *history_create(void)
{
    static char PATHNAME[MAXPATHLEN] = "";
    char *cwd = getcwd(PATHNAME, MAXPATHLEN);
    history_t *history = malloc(sizeof(history_t));

    history->entries = vec_create(100, sizeof(history_entry_t));
    history->destination = str_create(cwd);
    str_sadd(&history->destination, STR("/.42zsh_history"));
    return history;
}
