/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin echo
*/

#include <stdio.h>

#include "my_map.h"
#include "my_str.h"
#include "my_utils.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"

static void parse_escaped_char(str_t **arg)
{
    for (size_t i = 0; i < (*arg)->length; ++i) {
        if ((*arg)->data[i] != '\\')
            continue;
        str_erase_at_idx(arg, i);
        switch ((*arg)->data[i]) {
            case '\\': (*arg)->data[i] = '\\'; break;
            case 'a': (*arg)->data[i] = '\a'; break;
            case 'b': (*arg)->data[i] = '\b'; break;
            case 'e': (*arg)->data[i] = '\e'; break;
            case 'f': (*arg)->data[i] = '\f'; break;
            case 'n': (*arg)->data[i] = '\n'; break;
            case 'r': (*arg)->data[i] = '\r'; break;
            case 't': (*arg)->data[i] = '\t'; break;
        }
    }
}

static int parse_options(vec_str_t *av, bool *_e, bool *_n)
{
    size_t i = 1;

    for (; i < av->size; ++i) {
        if (str_eq(av->data[i], STR("-e"))) {
            *_e = true;
            continue;
        }
        if (str_eq(av->data[i], STR("-n"))) {
            *_n = true;
            continue;
        }
        break;
    }
    return i;
}

int builtin_echo(vec_str_t *av, shell_t UNUSED *state)
{
    bool _e = false;
    bool _n = false;
    size_t i = parse_options(av, &_e, &_n);

    for (; i < av->size; ++i) {
        if (_e)
            parse_escaped_char(&av->data[i]);
        str_print(av->data[i]);
        if (i + 1 < av->size)
            str_print(STR(" "));
    }
    if (!_n)
        str_print(STR("\n"));
    return 0;
}
