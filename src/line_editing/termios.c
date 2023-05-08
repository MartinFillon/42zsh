/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-martin.saldinger
** File description:
** termios
*/

#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <termios.h>

#include "my_str.h"

#include "mysh/termios.h"

static const char PROMPT[] = "\033[1;31m42zsh $>\033[0m ";

void print_prompt(str_t **input, size_t *pos)
{
    printf("\033[2K\r");
    printf("%s%s", PROMPT, (*input)->data);
    if ((*input)->length - *pos > 0)
        printf("\033[%ldD", (*input)->length - *pos);
    fflush(stdout);
}

static void setup_termios(struct termios *old_tio, struct termios *new_tio)
{
    tcgetattr(STDIN_FILENO, old_tio);
    *new_tio = *old_tio;
    new_tio->c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, new_tio);
    fflush(stdout);
}

str_t *handle_line_editing(shell_t *state)
{
    struct termios old_tio;
    struct termios new_tio;
    str_t *input = str_create("");

    printf("%s", PROMPT);
    setup_termios(&old_tio, &new_tio);
    read_termios(state, &input);
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return input;
}
