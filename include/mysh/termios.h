/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** termios
*/

#ifndef TERMIOS_H_
    #define TERMIOS_H_
    #include <stddef.h>
    #include <termios.h>
    #include <stdbool.h>
    #include "my_str.h"
    #define DELETE  127
    #define ENTER  '\n'
    #define ARROW  '['
    #define UP      'A'
    #define DOWN    'B'
    #define RIGHT   'C'
    #define LEFT    'D'
    #define KILL    4

str_t *stock_input(int ignore);
void print_prompt(str_t *input, size_t *pos);
void arrow_builtins(str_t *input, size_t *position);
void setup_termios(struct termios *old_tio, struct termios *new_tio);
str_t *manage_input(char c, bool *state, str_t *input, size_t *pos);
str_t* read_termios(str_t *input, int ignore, int *ignored, bool *state);
#endif /* !TERMIOS_H_ */
