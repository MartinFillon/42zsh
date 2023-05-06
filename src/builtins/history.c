/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "mysh/mysh.h"
#include "my_map.h"
#include "my_vec.h"

static const char *ERROR[] = {
    "history: Too many arguments.\n",
    "history: Badly formed number.\n",
    "Usage: history [-chrSLMT] [# number of events].\n"
};

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

static int check_hist_flags(void)
{
    dprintf(2, "%s", ERROR[2]);
    return 1;
}

static int check_hist_cases(vec_str_t *av, shell_t *state)
{
    size_t size = state->history->entries->size;

    if (str_isnum(av->data[1]) == 1){
        if (size > 100){
            print_history(state->history, size -
            (size > atof(av->data[1]->data)) ? atof(av->data[1]->data) : 100);
        } else {
            print_history(state->history, 0);
        }
    } else if (str_startswith(av->data[1], STR("-")) &&
        strcmp(av->data[1]->data, "-") != 0) {
            return check_hist_flags();
    } else {
        dprintf(2, "%s", ERROR[1]);
        return 1;
    }
    return 0;
}

int builtin_history(vec_str_t *av, shell_t *state)
{
    size_t hist_size = state->history->entries->size;

    if (av->size > 3) {
        dprintf(2, "%s", ERROR[0]);
        return 1;
    }
    if (av->size == 1 || (av->size == 2 &&
        strcmp(av->data[1]->data, "-") == 0)){
            print_history(state->history, (hist_size > 100) ?
            hist_size - 100 : 0);
            return 0;
    }
    if (av->size > 1){
        return check_hist_cases(av, state);
    }
    return 0;
}
