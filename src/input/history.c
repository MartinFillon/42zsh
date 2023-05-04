/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** history
*/

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "my_map.h"
#include "mysh/history.h"
#include "mysh/mysh.h"

void create_history(char *input)
{
    time_t now;
    time_t epoch;
    struct tm ts;
    FILE *fp = fopen(".42zsh_history", "a+");

    if (fp == NULL)
        return;

    time(&now);
    ts = *localtime(&now);
    epoch = mktime(&ts);
    fprintf(fp, "#+%ld\n", (long)epoch);
    fprintf(fp, "%s\n", input);
}
