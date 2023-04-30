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

static void delete_manager(size_t *pos, str_t *input)
{
    str_t *pre_input;
    str_t *post_input;
    if (*pos == input->length) {
        if (input->length <= 0)
                return;
            printf("\b \b");
            input->data[--input->length] = '\0';
            (*pos)--;
    } else {
        pre_input = str_substr(input, 0, *pos);
        post_input = str_substr(input, *pos + 1, input->length);
        str_sadd(&post_input, pre_input);
        printf("\n%s\n", pre_input->data);
        printf("\n%s\n", post_input->data);
    }
}

static void manage_input(char c, bool *state, str_t *input, size_t *pos)
{
    switch (c) {
        case ENTER:
            *state = false;
            return;
        case DELETE:
            delete_manager(pos, input);
            
            fflush(stdout);
            break;
        case ARROW:
            arrow_builtins(input, pos);
            break;
        default:
            if (c == 27)
                return;
            (*pos)++;
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
    size_t position;
    bool state = true;

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    fflush(stdout);
    while (state) {
        if (read(STDIN_FILENO, &c, 1) == 1)
            manage_input(c, &state, input, &position);
    }
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return input;
}
