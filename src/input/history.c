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

void create_history(char *input)
{
    time_t epoch_time;
    struct tm timeinfo;
    FILE *fp = fopen(".42zsh_history", "a+");

    if (fp == NULL)
        return;

    timeinfo = *localtime(&epoch_time);
    epoch_time = mktime(&timeinfo);
    fprintf(fp, "%s\n", input);
}
