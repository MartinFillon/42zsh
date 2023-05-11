/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

#include "my_map.h"

#include "mysh/history.h"
#include "mysh/mysh.h"

static char const *HIST_DEST = ".42zsh_history";

void history_append(char *input, history_t *history)
{
    if (strlen(input) == 0)
        return;

    time_t now = time(NULL);
    history_entry_t entry = {now, str_create(input)};
    vec_pushback(&history->entries, &entry);
    fprintf(
        history->dest, "#+%ld\n%s\n", VEC_LAST(history->entries).timestamp,
        VEC_LAST(history->entries).command->data
    );
}

void history_free(history_t *history)
{
    for (size_t i = 0; i < history->entries->size; i++) {
        free(history->entries->data[i].command);
    }
    free(history->entries);
    fclose(history->dest);
}

static void load_history(FILE *hist, history_t *history)
{
    char *input = NULL;
    size_t l_cap = 0;
    ssize_t l_size = 0;
    history_entry_t tmp = {0};

    while ((l_size = getline(&input, &l_cap, hist)) > 0) {
        input[l_size - 1] = '\0';

        if (input[0] == '#' && strlen(input) > 2) {
            tmp.timestamp = atoi(input + 2);
        } else {
            tmp.command = str_create(input);
            vec_pushback(&history->entries, &tmp);
            memset(&tmp, 0, sizeof(history_entry_t));
        }
    }
    free(input);
}

history_t history_create(void)
{
    history_t history = {
        .entries = vec_create(100, sizeof(history_entry_t)),
        .dest = fopen(HIST_DEST, "a+"),
    };

    FILE *hist = fopen(HIST_DEST, "r");

    if (hist != NULL) {
        load_history(hist, &history);
        fclose(hist);
    }
    return history;
}
