/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** manage input
*/

#include <stdbool.h>
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

bool manage_input(char c, str_t **input, size_t *pos)
{
    switch (c) {
        case ESCAPE: break;
        case ENTER: print_prompt(input, pos); return true;
        case SUPPR: suppr_char(pos, input); break;
        case DELETE: delete_char(pos, input); break;
        case ARROW: handle_arrows(input, pos); break;
        case KILL:
            free(*input);
            *input = NULL;
            return true;
        default: add_char(pos, input, c); break;
    }
    print_prompt(input, pos);
    return false;
}
