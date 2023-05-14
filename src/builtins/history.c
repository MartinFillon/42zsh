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
#include <time.h>

#include "my_map.h"
#include "my_vec.h"

#include "mysh/mysh.h"
#include "mysh/history.h"

static const char *TOO_MANY = "history: Too many arguments.\n";
static const char *BAD_FORM = "history: Badly formed number.\n";
static const char *USAGE = "Usage: history [-chrSLMT] [# number of events].\n";

static void edited_history(history_t *history, char flag, size_t start)
{
    struct tm *time;

    if (flag == 'h'){
        for (size_t i = start; i < history->entries->size; i++) {
            printf("%s\n", history->entries->data[i].command->data);
        }
    }
    if (flag == 'r'){
        for (size_t i = history->entries->size - 1; i > start; i--) {
            time = localtime(&history->entries->data[i].timestamp);
            printf(
                "%5ld  %01d:%02d   %s\n", i + 1, time->tm_hour, time->tm_min,
                history->entries->data[i].command->data
            );
        }
    }
}

static void print_history(history_t *history, size_t start)
{
    struct tm *time;

    if (history->entries->size == 0)
        return;
    for (size_t i = start; i < history->entries->size; i++) {
        time = localtime(&history->entries->data[i].timestamp);
        if (time == NULL)
            return;
        printf(
            "%5ld  %01d:%02d   %s\n", i + 1, time->tm_hour, time->tm_min,
            history->entries->data[i].command->data
        );
    }
}

static int setup_flags(vec_str_t *av, shell_t *state)
{
    size_t size = state->history.entries->size;

    for (size_t i = 1;i < av->data[1]->length; i++){
        switch (av->data[1]->data[i]) {
            case 'c': vec_clear(&state->history.entries); break;
            case 'h': edited_history(&state->history, 'h', (size < 100) ? 0 :
                (size - 100)); break;
            case 'r': edited_history(&state->history, 'r', (size < 100) ? 0 :
                (size - 100)); break;
            case 'S': save_history(&state->history, av->data[2]->data); break;
            case 'L': load_diff_hist(&state->history, av->data[2]->data); break;
            case 'M': load_diff_hist(&state->history, av->data[2]->data); break;
            case 'T': print_history(&state->history, (size < 100) ? 0 :
                (size - 100)); break;
            default: dprintf(2, "%s", USAGE); return 1;
        }
    }
    return 0;
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
        return setup_flags(av, state);
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
