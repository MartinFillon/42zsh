/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** termios
*/

#ifndef TERMIOS_H_
    #define TERMIOS_H_
    #include "my_str.h"
    #define DELETE  127
    #define ENTER  '\n'
    #define ARROW  '['
    #define UP      'A'
    #define DOWN    'B'
    #define RIGHT   'C'
    #define LEFT    'D'
    #define KILL    4

str_t *stock_input(void);
void print_prompt(str_t *input, size_t *pos);
void arrow_builtins(str_t *input, size_t *position);

#endif /* !TERMIOS_H_ */
