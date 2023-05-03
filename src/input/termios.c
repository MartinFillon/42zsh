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

#include "mysh/termios.h"
#include "my_str.h"

static void arrow_builtins(char c)
{
    if (read(STDIN_FILENO, &c, 1) == 1) {
        switch (c) {
            case UP: break;
            case DOWN: break;
            case RIGHT: break;
            case LEFT: break;
        }
    }
}

static void manage_input(char c, bool *state, str_t *input)
{
    switch (c) {
        case ENTER: *state = false; return;
        case DELETE:
            if (input->length <= 0)
                return;
            printf("\b \b");
            input->data[--input->length] = '\0';
            fflush(stdout);
            break;
        case ARROW: arrow_builtins(c); break;
        default:
            write(1, &c, 1);
            str_cadd(&input, c);
            fflush(stdout);
            break;
    }
}

str_t *stock_input(void)
{
    struct termios old_tio;
    struct termios new_tio;
    str_t *input = str_create("");
    char c;
    bool state = true;

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    fflush(stdout);
    while (state) {
        if (read(STDIN_FILENO, &c, 1) == 1)
            manage_input(c, &state, input);
    }
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return input;
}
