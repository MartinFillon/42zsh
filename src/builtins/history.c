/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "my_map.h"
#include "my_vec.h"

#include "mysh/mysh.h"

static const char *TOO_MANY = "history: Too many arguments.\n";
static const char *BAD_FORM = "history: Badly formed number.\n";
static const char *USAGE = "Usage: history [-chrSLMT] [# number of events].\n";

static void print_history(history_t *history, size_t start)
{
    struct tm *time;

    for (size_t i = start; i < history->entries->size; i++) {
        time = localtime(&history->entries->data[i].timestamp);
        printf(
            "%5ld  %01d:%02d   %s\n", i + 1, time->tm_hour, time->tm_min,
            history->entries->data[i].command->data
        );
    }
}

static int check_hist_cases(vec_str_t *av, shell_t *state)
{
    size_t size = state->history.entries->size;

    if (str_isnum(av->data[1]) == 1) {
        if (size > 100) {
            print_history(&state->history,
            size - ((size > atof(av->data[1]->data)) ?
            atof(av->data[1]->data) : 100));
        } else {
            print_history(&state->history, (size > atof(av->data[1]->data)) ?
            size - atof(av->data[1]->data) : 0);
        }
        return 0;
    }
    if (str_startswith(av->data[1], STR("-")) &&
        !str_eq(av->data[1], STR("-"))) {
        dprintf(2, "%s", USAGE);
        return 1;
    }
    dprintf(2, "%s", BAD_FORM);
    return 1;
}

int builtin_history(vec_str_t *av, shell_t *state)
{
    size_t hist_size = state->history.entries->size;

    if (av->size > 3) {
        dprintf(2, "%s", TOO_MANY);
        return 1;
    }
    if (av->size == 1 || (av->size == 2 && str_eq(av->data[1], STR("-")))) {
        print_history(&state->history, (hist_size > 100) ? hist_size - 100 : 0);
        return 0;
    }
    if (av->size > 1) {
        return check_hist_cases(av, state);
    }
    return 0;
}
