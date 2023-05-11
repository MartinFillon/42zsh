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

void print_prompt(char *prompt, struct input_s *input)
{
    printf("\033[2K\r");
    printf("%s%s", prompt, (*input->input)->data);
    if ((*input->input)->length - input->pos > 0)
        printf("\033[%ldD", (*input->input)->length - input->pos);
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

str_t *handle_line_editing(shell_t *state, char *prompt)
{
    struct termios old_tio;
    struct termios new_tio;
    struct input_s input = {&(str_t *){str_create("")}, 0, 0};

    printf("%s", prompt);
    setup_termios(&old_tio, &new_tio);
    read_termios(prompt, state, &input);
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return (*input.input);
}
