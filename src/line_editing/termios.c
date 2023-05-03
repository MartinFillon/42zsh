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
#include <curses.h>
#include <unistd.h>
#include <term.h>

#include "my_str.h"
#include "mysh/termios.h"

static void arrow_builtins(str_t *input, size_t *pos)
{
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        switch (c) {
            case UP:
                break;
            case DOWN:
                break;
            case RIGHT:
                if ((*pos) >= input->length)
                    return;
                (*pos)++;
                printf("\033[1C");
                break;
            case LEFT:
                if ((*pos) <= 0)
                    return;
                (*pos)--;
                printf("\033[1D");
                break;
        }
    }
    fflush(stdout);
}

static str_t *delete_manager(size_t *pos, str_t *input)
{
    str_t *pre_input;
    str_t *post_input;

    if (*pos == input->length) {
        if (input->length <= 0)
                return input;
            input->data[--input->length] = '\0';
            printf("\b\b");
    } else {
        pre_input = str_substr(input, 0, *pos - 1);
        post_input = str_substr(input, *pos, input->length - (*pos));
        str_sadd(&pre_input, post_input);
        input = pre_input;
        printf("\b");
        delch();

    }
    (*pos)--;
    return input;
}

static str_t *manage_input(char c, bool *state, str_t *input, size_t *pos)
{
    switch (c) {
        case ENTER:
            *state = false;
            return input;
        case DELETE:
            input = delete_manager(pos, input);
            fflush(stdout);
            break;
        case ARROW:
            arrow_builtins(input, pos);
            break;
        default:
            if (c == 27)
                return input;
            (*pos)++;
            write(1, &c, 1);
            str_cadd(&input, c);
            fflush(stdout);
            break;
    }
    return input;
}

str_t *stock_input(void)
{
    struct termios old_tio;
    struct termios new_tio;
    str_t *input = str_create("");
    char c;
    size_t position = 0;
    bool state = true;

    //initscr();
    //cbreak();
    //noecho();
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    fflush(stdout);
    while (state) {
        if (read(STDIN_FILENO, &c, 1) == 1)
            input = manage_input(c, &state, input, &position);
    }
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return input;
}
