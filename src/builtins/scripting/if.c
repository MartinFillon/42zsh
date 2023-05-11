/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** if
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mysh/exec.h"
#include "mysh/history.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"
#include "my_btree.h"
#include "my_str.h"

size_t parenthesis_case(vec_str_t *av, str_t **cond)
{
    str_add(cond, av->data[1]->data + 1);
    str_cadd(cond, ' ');

    for (size_t i = 2; i < av->size; i++) {
        if (str_endswith(av->data[i], STR(")"))) {
            av->data[i]->data[av->data[i]->length - 1] = '\0';
            str_sadd(cond, av->data[i]);
            return i + 1;
        }
        str_sadd(cond, av->data[i]);
        str_cadd(cond, ' ');
    }
    return av->size + 1;
}

size_t get_condition(vec_str_t *av, str_t **cond)
{
    if (str_eq(av->data[1], STR("1")) || str_eq(av->data[1], STR("0"))) {
        str_sadd(cond, av->data[1]);
        return 2;
    }
    if (str_startswith(av->data[1], STR("(")))
        return parenthesis_case(av, cond);
    else {
        str_sadd(cond, av->data[1]);
        str_cadd(cond, ' ');
        str_sadd(cond, av->data[2]);
        str_cadd(cond, ' ');
        str_sadd(cond, av->data[3]);
        return 4;
    }
}

void get_commands(vec_str_t *av, str_t **command, size_t i)
{
    for (; i < av->size; i++) {
        str_sadd(command, av->data[i]);
        str_cadd(command, ' ');
    }
}

int builtin_if(vec_str_t *av, shell_t *state)
{
    str_t *cond = str_create("test ");
    str_t *command_true = str_create("");

    if (av->size < 2) {
        dprintf(2, "if: Too few arguments.\n");
        return 1;
    }
    size_t i = get_condition(av, &cond);
    get_commands(av, &command_true, i);
    int ret = exec_sub_proc(state, cond);

    if (ret == 0)
        exec_sub_proc(state, command_true);
    return 0;
}
