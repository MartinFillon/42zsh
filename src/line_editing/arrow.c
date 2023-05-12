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

#include "mysh/history.h"
#include "mysh/mysh.h"
#include "mysh/termios.h"

static void move_left_in_line(shell_input_t *in)
{
    if (in->pos == 0)
        return;

    in->pos--;
    printf("\033[1D");
    fflush(stdout);
}

static void move_right_in_line(shell_input_t *in)
{
    if (in->pos == in->input->length)
        return;

    in->pos++;
    printf("\033[1C");
    fflush(stdout);
}

static void move_down_history(shell_input_t *in, history_t *hist)
{
    size_t size = hist->entries->size;

    if (size == 0)
        return;
    if (in->history_pos <= size && in->history_pos > 0)
        in->history_pos--;
    if (in->input)
        free(in->input);

    in->input = (in->history_pos == 0)
        ? str_create("")
        : str_dup(hist->entries->data[size - in->history_pos].command);
    in->pos = in->input->length;
    fflush(stdout);
}

static void move_up_history(shell_input_t *in, history_t *hist)
{
    size_t size = hist->entries->size;

    if (size == 0)
        return;
    if (in->history_pos < size)
        in->history_pos++;
    if (in->input)
        free(in->input);
    in->input = str_dup(hist->entries->data[size - in->history_pos].command);
    in->pos = in->input->length;
    fflush(stdout);
}

bool handle_arrows(char c, shell_input_t *input, shell_t *state)
{
    switch (c) {
        case UP: move_up_history(input, &state->history); break;
        case DOWN: move_down_history(input, &state->history); break;
        case RIGHT: move_right_in_line(input); break;
        case LEFT: move_left_in_line(input); break;
        default: return false;
    }
    return true;
}
