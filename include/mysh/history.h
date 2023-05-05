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

history_t *history_create(void);

void history_append(char *input, history_t *history);

void save_history(history_t *history);

#endif /* MYSH_HISTORY_*/