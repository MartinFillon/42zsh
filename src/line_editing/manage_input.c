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
    char *c, str_t **input, size_t *pos, shell_t *state
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
        suppr_char(pos, input);
    } else if (handle_arrows(*c, input, pos, state) == false) {
        return false;
    }
    print_prompt(input, pos);
    return true;
}

bool manage_input(char c, str_t **input, size_t *pos, shell_t *state)
{
    if (c == ESCAPE && handle_composed_char(&c, input, pos, state))
        return false;

    switch (c) {
        case KILL: free(*input); *input = NULL; return true;
        case ENTER: print_prompt(input, pos); return true;
        case DELETE: delete_char(pos, input); break;
        default: if (isprint(c)) add_char(pos, input, c);
    }
    print_prompt(input, pos);
    return false;
}
