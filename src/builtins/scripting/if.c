/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** if
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "my_str.h"

#define EQUAL 1
#define NOT_EQUAL 0

static int exec_on_condition(vec_str_t *av, shell_t *state, int operation)
{
    int right = str_toint(av->data[3]);
    int left = str_toint(av->data[1]);
    str_t *to_exec = NULL;

    if ((left == right) == operation) {
        if (av->size < 5) {
            dprintf(2, "if: Empty if.\n");
            return 1;
        }
        to_exec = str_dup(av->data[4]);
        for (size_t i = 5; i < av->size; i++) {
            str_cadd(&to_exec, ' ');
            str_sadd(&to_exec, av->data[i]);
        }
    }
    exec_wrapper(state, to_exec->data);
    return state->return_code;
}

int builtin_if(vec_str_t *av, shell_t __attribute__((unused)) *state)
{
    str_t *to_exec = NULL;

    if (av->size < 3) {
        dprintf(2, "if: Empty if.\n");
        return 1;
    }
    if (!str_isnum(av->data[1]))
        return 1;
    if (str_compare(av->data[2], STR("==")) == 0 && str_isnum(av->data[3]))
        return exec_on_condition(av, state, EQUAL);
    if (str_compare(av->data[2], STR("!=")) == 0 && str_isnum(av->data[3]))
        return exec_on_condition(av, state, NOT_EQUAL);
    to_exec = str_dup(av->data[2]);
    for (size_t i = 3; i < av->size; i++) {
        str_cadd(&to_exec, ' ');
        str_sadd(&to_exec, av->data[i]);
    }
    exec_wrapper(state, to_exec->data);
    return 0;
}
