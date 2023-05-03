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

typedef struct history_s {
    vec_int_t id;
    time_t timestamp;
    vec_str_t command;
} history_t;


void create_history(char *input);

#endif /* MYSH_HISTORY_*/
