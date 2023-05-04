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

// void start_history(shell_t *state, char *input)
// {
//     (void)input;
//     state->history->entries = vec_create(5000, sizeof(history_t));
// }

void history_append(char *input, history_t *history)
{
    time_t now;
    time_t epoch;
    struct tm ts;
    printf("%s\n", history->destination->data);
    FILE *fp = fopen(history->destination->data, "a+");

    if (fp == NULL)
        return;

    time(&now);
    ts = *localtime(&now);
    epoch = mktime(&ts);
    fprintf(fp, "#+%ld\n", (long)epoch);
    fprintf(fp, "%s\n", input);
}

history_t *history_create(void)
{
    static char PATHNAME[MAXPATHLEN] = "";
    char *cwd = getcwd(PATHNAME, MAXPATHLEN);
    str_t *file = str_create("/.42zsh_history");
    history_t *history = malloc(sizeof(history_t));

    history->destination = str_create(cwd);
    str_sadd(&history->destination, file);
    return history;
}
