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

typedef struct hystry_entry_s {
    int id;
    time_t timestamp;
    vec_str_t command;
} history_entry_t;

VEC_DEF(history_entry_t, history_entry);

typedef struct hystory_s history_t;

void history_append(char *input, history_t *history);

#endif /* MYSH_HISTORY_*/
