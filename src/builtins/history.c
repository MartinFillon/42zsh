/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mysh/mysh.h"
#include "my_map.h"
#include "my_vec.h"

static const char *ERROR[] = {
    "history: Too many arguments.\n",
    "history: Badly formed number.\n",
};

int builtin_history(vec_str_t *av, shell_t *state)
{
    (void)state;

    if (av->size > 3) {
        dprintf(2, "%s", ERROR[0]);
        return 1;
    }

    return 0;
}