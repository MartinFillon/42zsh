/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#ifndef MYSH_HISTORY_
    #define MYSH_HISTORY_

    #include <time.h>
    #include <stdbool.h>

    #include "my_map.h"

typedef struct history_entry_s {
    time_t timestamp;
    str_t *command;
} history_entry_t;

VEC_DEF(history_entry_t, history_entry)

typedef struct history_s history_t;

// HISTORY
history_t history_create(void);
void history_free(history_t *history);
void history_append(char *input, history_t *history);

// EXCLAMATION POINTS
typedef struct shell_s shell_t;
bool get_exclamation(str_t **line, shell_t *state);


#endif /* MYSH_HISTORY_*/
