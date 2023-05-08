/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** exclamation
*/

#include "mysh/mysh.h"
#include "mysh/history.h"

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void travel_history(history_t *history, size_t pos)
{
    size_t size = history->entries->size;

    printf("%s\n", history->entries->data[size + pos].command->data);
}

char *get_history_str(history_t *history, char *input)
{
    for (size_t i = 0;i < history->entries->size; i++){
        if (strncmp(input, history->entries->data[i].command->data,
            strlen(input)) == 0){
            return history->entries->data[i].command->data;
        }
    }
    return NULL;
}

void get_history_index(history_t *history, size_t index)
{
    printf("%s\n", history->entries->data[index + 1].command->data);
}

int exclamation_conditions(history_t *history, str_t *command)
{
    char *DOUB = NULL;

    if (command->data[0] == '!') {
        printf("1\n");
        travel_history(history, -2);
        return 0;
    }
    if (isdigit(command->data[0])) {
        printf("2\n");
        get_history_index(history, atoi(command->data));
        return 0;
    }
    if (command->data[0] == '-') {
        printf("3\n");
        get_history_index(history, -atoi(command->data + 1));
        return 0;
    }
    DOUB = get_history_str(history, command->data);
    printf("%s\n", DOUB);
    return 0;
}
