/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** setup_termios
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "mysh/termios.h"
#include "my_str.h"

void setup_termios(struct termios *old_tio, struct termios *new_tio)
{
    tcgetattr(STDIN_FILENO, old_tio);
    new_tio = old_tio;
    new_tio->c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, new_tio);
    fflush(stdout);
}

str_t* read_termios(str_t *input, int ignore, int *ignored, bool *state)
{
    char c;
    size_t position = 0;

    if (read(STDIN_FILENO, &c, 1) == 1)
        input = manage_input(c, state, input, &position);
    if (input == (str_t *) -1 && *ignored >= ignore)
        return NULL;
    if (input == (str_t *) -1) {
        *state = true;
        (*ignored)++;
    }
    return input;
}
