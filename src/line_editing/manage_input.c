/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** manage input
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_str.h"

#include "mysh/termios.h"

static void suppr_char(size_t *pos, str_t **input)
{
    size_t len = (*input)->length;
    size_t to_rm = (len == 1 || len == *pos + 1) ? *pos : *pos + 1;

    if (len == 0 || *pos > len)
        return;

    str_erase_at_idx(input, to_rm);
}

static void delete_char(size_t *pos, str_t **input)
{
    if ((*input)->length == 0 || *pos == 0)
        return;

    str_erase_at_idx(input, *pos - 1);
    --*pos;
}

static void add_char(size_t *pos, str_t **input, char c)
{
    str_insert_at_idx(input, *pos, c);
    ++*pos;
}

static bool handle_composed_char(
    char *prompt, char *c, struct input_s *input, shell_t *state
)
{
    read(STDIN_FILENO, c, 1);
    if (*c != COMPOSED)
        return false;

    read(STDIN_FILENO, c, 1);
    if (*c == BEFORE_SUPPR) {
        read(STDIN_FILENO, c, 1);
        if (*c != SUPPR) {
            return false;
        }
        suppr_char(&input->pos, input->input);
    } else if (handle_arrows(*c, input, state) == false) {
        return false;
    }
    print_prompt(prompt, input);
    return true;
}

bool manage_input(
    char *prompt, char c, struct input_s *input, shell_t *state
)
{
    if (c == ESCAPE && handle_composed_char(prompt, &c, input, state))
        return false;

    switch (c) {
        case KILL:
            free(*input->input);
            *input->input = NULL;
            return true;
        case ENTER: print_prompt(prompt, input); return true;
        case DELETE: delete_char(&input->pos, input->input); break;
        default:
            if (isprint(c))
                add_char(&input->pos, input->input, c);
    }
    print_prompt(prompt, input);
    return false;
}
