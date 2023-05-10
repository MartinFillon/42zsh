/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** repeat
*/

#include <stdio.h>
#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "my_str.h"

static char *get_command(vec_str_t *av)
{
    str_t *tmp = NULL;

    tmp = str_dup(av->data[2]);
    for (size_t i = 3; i < av->size; i++) {
        str_cadd(&tmp, ' ');
        str_sadd(&tmp, av->data[i]);
    }
    return tmp->data;
}

int builtin_repeat(vec_str_t *av, shell_t *state)
{
    char *command = NULL;

    if (av->size < 3) {
        dprintf(2, "repeat: Too few arguments.\n");
        return 1;
    }
    if (!str_isnum(av->data[1])) {
        dprintf(2, "repeat: Badly formed number.\n");
        return 1;
    }
    command = get_command(av);
    for (int i = 0; i < str_toint(av->data[1]); i++)
        exec_wrapper(state, command);
    return state->return_code;
}
