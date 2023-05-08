/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** exclamation
*/

#include "mysh/mysh.h"
#include "mysh/history.h"

history_t *travel_history(history_t *history, size_t position)
{
    size_t size = history->entries->size;
    size_t new_pos = size + position;

    printf("[%s]\n", history->entries->data[new_pos].command->data);
}

// int backstep_history()
// !! -> latest command
// up arrow -> -1 command in history

// int latest_nbr_command()
// ![number] -> latest command number

// int latest_input_command()
// ![character/ string] -> latest command starting with character/ string

// REMEMBER THAT PRECEDING ARGUMENTS ARE ALSO CONSIDERED AS THEY ARE
