/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-martin.saldinger
** File description:
** termios
*/

#include "my_str.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static const int DELETE = 127;

static void manage_input(char c, bool *state, str_t *input)
{
    if (c == '\n') {
        *state = false;
        return;
    }
    if (c == DELETE) {
        printf("\b \b");
        input->data[--input->length] = '\0';
        fflush(stdout);
    } else {
        write(1, &c, 1);
        str_cadd(&input, c);
        fflush(stdout);
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
