/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** arrow
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "my_str.h"

#include "mysh/termios.h"

static void move_left_in_line(size_t *pos)
{
    if (*pos == 0)
        return;

    --*pos;
    printf("\033[1D");
    fflush(stdout);
}

static void move_right_in_line(size_t *pos, str_t *input)
{
    if (*pos >= input->length)
        return;

    ++*pos;
    printf("\033[1C");
    fflush(stdout);
}

bool handle_arrows(char c, str_t **input, size_t *pos)
{
    switch (c) {
        case UP: break;
        case DOWN: break;
        case RIGHT: move_right_in_line(pos, *input); break;
        case LEFT: move_left_in_line(pos); break;
        default: return false;
    }

    return true;
}
