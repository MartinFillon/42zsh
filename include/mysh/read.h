/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** read declarations
*/

#ifndef MYSH_READ_H
    #define MYSH_READ_H
    #include "my_str.h"
    #include "my_map.h"

    #include "mysh/mysh.h"


void read_input(shell_t *state);

void catch_signals(void);

vec_str_t *parse_args(map_t *env, char *line);
str_t *parse_variables(char *line, map_t *env);

map_t *env_create(char **env);

#endif /* MYSH_READ_H */