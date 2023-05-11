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

#include "mysh/mysh.h"
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

static void move_down_history(
    size_t *pos, str_t *input, shell_t *state, size_t *index
)
{
    (void)input;
    size_t size = state->history.entries->size;
    index = pos;

    if (size == 0)
        return;
    if (*index <= size)
        --*index;
    if (*index <= 0){
        *index = 1;
        return;
    }
    printf("\015");
    printf("%s", state->history.entries->data[size - *index].command->data);
    fflush(stdout);
}

static void move_up_history(
    size_t *pos, str_t *input, shell_t *state, size_t *index
)
{
    (void)input;
    size_t size = state->history.entries->size;
    index = pos;

    if (size == 0)
        return;
    if (*index < size)
        ++*index;
    printf("\015");
    printf("%s", state->history.entries->data[size - *index].command->data);
    fflush(stdout);
}

bool handle_arrows(char c, str_t **input, size_t *pos, shell_t *state)
{
    size_t index = 0;

    switch (c) {
        case UP: move_up_history(pos, *input, state, &index); break;
        case DOWN: move_down_history(pos, *input, state, &index); break;
        case RIGHT: move_right_in_line(pos, *input); break;
        case LEFT: move_left_in_line(pos); break;
        default: return false;
    }
    return true;
}
