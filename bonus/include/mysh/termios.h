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

    #include "mysh/mysh.h"

    #define DELETE      (127)
    #define KILL        (4)
    #define ENTER       ('\n')

    #define ESCAPE      (27)

    #define COMPOSED    ('[')

    #define BEFORE_SUPPR  (51)
    #define SUPPR         ('~')

    #define UP     ('A')
    #define DOWN   ('B')
    #define RIGHT  ('C')
    #define LEFT   ('D')

typedef struct {
    str_t *input;
    size_t pos;
    size_t history_pos;
} shell_input_t;

str_t *handle_line_editing(shell_t *state, char const *prompt);
void print_prompt(char const *prompt, shell_input_t *input);
void read_termios(char const *prompt, shell_t *state, shell_input_t *input);
bool handle_arrows(char c, shell_input_t *input, shell_t *state);
bool manage_input(
    char const *prompt, char c, shell_input_t *input, shell_t *state
);

#endif /* !TERMIOS_H_ */
