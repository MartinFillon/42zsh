/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-martin.saldinger
** File description:
** termios
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "my_str.h"

#include "mysh/termios.h"

const char PROMPT[] = "\033[1;31m42zsh $>\033[0m ";

void print_prompt(str_t **input, size_t *pos)
{
    printf("\033[2K\r");
    printf("%s%s", PROMPT, (*input)->data);
    if ((*input)->length - *pos > 0)
        printf("\033[%ldD", (*input)->length - *pos);
    fflush(stdout);
}

str_t *handle_line_editing(void)
{
    struct termios old_tio;
    struct termios new_tio;
    str_t *input = str_create("");
    char c;
    size_t pos = 0;

    printf("%s", PROMPT);
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    fflush(stdout);

    while (read(STDIN_FILENO, &c, 1) == 1)
        if (manage_input(c, &input, &pos))
            break;

    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return input;
}
