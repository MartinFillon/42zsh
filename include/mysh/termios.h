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

str_t *handle_line_editing(shell_t *state, char *prompt);
void print_prompt(char *prompt, str_t **input, size_t *pos);
void read_termios(char *prompt, shell_t *state, str_t **input);
bool handle_arrows(char c, str_t **input, size_t *pos, shell_t *state);
bool manage_input(
    char *prompt, char c, str_t **input, size_t *pos, shell_t *state
);

#endif /* !TERMIOS_H_ */
