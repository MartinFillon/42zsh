/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** termios
*/

#ifndef TERMIOS_H_
    #define TERMIOS_H_

    #include <stdbool.h>

    #include "my_str.h"

    #define DELETE  (127)
    #define ENTER   ('\n')
    #define ESCAPE  (27)
    #define SUPPR   ('~')
    #define ARROW   ('[')
    #define UP      ('A')
    #define DOWN    ('B')
    #define RIGHT   ('C')
    #define LEFT    ('D')
    #define KILL    (4)

str_t *handle_line_editing(void);
void print_prompt(str_t **input, size_t *pos);
void handle_arrows(str_t **input, size_t *pos);
bool manage_input(char c, str_t **input, size_t *pos);

#endif /* !TERMIOS_H_ */
