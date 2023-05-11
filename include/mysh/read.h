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

void restore_signals(void);

void remove_escaped_chars_and_quotes(str_t *arg);

vec_str_t *parse_args(shell_t *state, char const *line);

vec_str_t *split_args(str_t *line);

str_t *exec_backticks(shell_t *state, str_t *line);

str_t *exec_sub_shell(shell_t *state, str_t *line);

int exec_sub_proc(shell_t *state, str_t *cmd);

str_t *parse_variables(char const *line, shell_t *state);

vec_str_t *get_globbings(vec_str_t *args);

map_t *env_create(char const *const *env);

#endif /* MYSH_READ_H */
