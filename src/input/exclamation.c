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

char *travel_history(history_t *history, size_t pos)
{
    size_t size = history->entries->size;

    return history->entries->data[size + pos].command->data;
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

char *get_history_index(history_t *history, size_t index)
{
    return history->entries->data[index + 1].command->data;
}

char *exclamation_conditions(history_t *history, str_t *command)
{
    char *result = NULL;

    if (str_compare(command, STR("!")) == 0) {
        return travel_history(history, -2);
    }
    if (str_isnum(command) == 1) {
        return get_history_index(history, atoi(command->data));
    }
    result = get_history_str(history, command->data);
    if (result == NULL){
        printf("->>>");
        str_print(command);
    }
    return result;
}
