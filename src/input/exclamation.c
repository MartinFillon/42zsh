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

static str_t *get_history_str(history_t *history, char *input)
{
    if (history->entries->size == 0)
        return NULL;
    for (size_t i = history->entries->size - 1;i > 0; i--){
        if (strncmp(input, history->entries->data[i].command->data,
            strlen(input)) == 0){
            return history->entries->data[i].command;
        }
    }
    if (strncmp(input, history->entries->data[0].command->data,
        strlen(input)) == 0){
        return history->entries->data[0].command;
    }
    return NULL;
}

static str_t *exclamation_conditions(history_t *history, str_t *input)
{
    size_t size = history->entries->size;

    if (str_compare(input, STR("!")) == 0) {
        return history->entries->data[size - 1].command;
    }
    if (str_isnum(input) == 1) {
        return history->entries->data[atoi(input->data) - 1].command;;
    } else {
        return get_history_str(history, input->data);
    }
    return NULL;
}

int get_exclamation(str_t **line, shell_t *state)
{
    str_t *designator = NULL;
    str_t *tmp = NULL;
    long index = str_find(*line, STR("!"), 0);

    designator = str_ncreate((*line)->data + index, (*line)->length - index);
    str_erase_at_idx(&designator, 0);
    tmp = exclamation_conditions(&state->history, designator);
    free(designator);
    if (tmp != NULL){
        str_insert_str(line, index, tmp);
        str_slice(line, 0, index + tmp->length);
        printf("%s\n", (*line)->data);
        return 0;
    }
    dprintf(2, "%s: Event not found.\n", (*line)->data);
    return 1;
}
