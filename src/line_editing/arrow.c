/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** arrow
*/

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "my_str.h"

#include "mysh/mysh.h"
#include "mysh/termios.h"

static void move_left_in_line(struct input_s *input)
{
    if (input->pos == 0)
        return;

    --input->pos;
    printf("\033[1D");
    fflush(stdout);
}

static void move_right_in_line(struct input_s *input)
{
    if (input->pos == (*input->input)->length)
        return;

    ++input->pos;
    printf("\033[1C");
    fflush(stdout);
}

static void move_down_history(struct input_s *input, shell_t *state)
{
    size_t size = state->history.entries->size;

    if (size == 0)
        return;
    if (input->history_position <= size)
        --input->history_position;
    if (input->history_position == UINT64_MAX || input->history_position == 0) {
        input->history_position = 1;
        return;
    }
    if (*input->input)
        free(*input->input);
    *input->input =
        str_dup(state->history.entries->data[size - input->history_position].command);
    input->pos = (*input->input)->length;
    fflush(stdout);
}

static void move_up_history(struct input_s *input, shell_t *state)
{
    size_t size = state->history.entries->size;

    if (size == 0)
        return;
    if (input->history_position < size)
        ++input->history_position;
    if (*input->input)
        free(*input->input);
    *input->input =
        str_dup(state->history.entries->data[size - input->history_position].command);
    input->pos = (*input->input)->length;
    fflush(stdout);
}

bool handle_arrows(char c, struct input_s *input, shell_t *state)
{
    switch (c) {
        case UP: move_up_history(input, state); break;
        case DOWN: move_down_history(input, state); break;
        case RIGHT: move_right_in_line(input); break;
        case LEFT: move_left_in_line(input); break;
        default: return false;
    }
    return true;
}
