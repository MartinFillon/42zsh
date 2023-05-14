/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** manage input
*/

#include <ctype.h>
#include <glob.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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
    char const *prompt, char *c, shell_input_t *in, shell_t *state
)
{
    read(STDIN_FILENO, c, 1);
    if (*c != COMPOSED)
        return false;

    read(STDIN_FILENO, c, 1);
    if (*c == BEFORE_SUPPR) {
        read(STDIN_FILENO, c, 1);
        if (*c != SUPPR)
            return false;

        suppr_char(&in->pos, &in->input);
    } else if (handle_arrows(*c, in, state) == false)
        return false;

    print_prompt(prompt, in);
    return true;
}

bool manage_input(char const *prompt, char c, shell_input_t *in, shell_t *state)
{
    if (c == ESCAPE && handle_composed_char(prompt, &c, in, state))
        return false;

    switch (c) {
        case TAB: tab_show_possibilities(in, state); break;
        case KILL:
            free(in->input);
            in->input = NULL;
            return true;
        case ENTER: print_prompt(prompt, in); return true;
        case DELETE: delete_char(&in->pos, &in->input); break;
        default:
            if (isprint(c))
                add_char(&in->pos, &in->input, c);
    }
    print_prompt(prompt, in);
    return false;
}
