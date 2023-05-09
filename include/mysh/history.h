/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#ifndef MYSH_HISTORY_
    #define MYSH_HISTORY_

    #include "my_map.h"

    #include <time.h>

typedef struct history_entry_s {
    time_t timestamp;
    str_t *command;
} history_entry_t;

VEC_DEF(history_entry_t, history_entry)

typedef struct history_s history_t;

void history_free(history_t *history);

history_t history_create(void);

void history_append(char *input, history_t *history);

void save_history(history_t *history);

// EXCLAMATION POINT

typedef struct shell_s shell_t;

int get_exclamation(str_t **line, long i, shell_t *state);

str_t *exclamation_conditions(history_t *history, str_t *command);

#endif /* MYSH_HISTORY_*/
