/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** jobs builtin
*/

#include <stdio.h>

#include "my_utils.h"

#include "mysh/mysh.h"

int builtin_jobs(vec_str_t UNUSED *av, shell_t *state)
{
    for (size_t i = 0; i < state->jobs->size; ++i) {
        printf("[%ld] %d\n", i + 1, state->jobs->data[i]);
    }

    return 0;
}
