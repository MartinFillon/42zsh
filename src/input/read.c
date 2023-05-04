/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** read
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_btree.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/history.h"
#include "mysh/termios.h"

const char PROMPT[] = "\033[1;31m42zsh $>\033[0m ";

static void print_prompt(shell_t *state)
{
    if (state->is_atty) {
        write(1, PROMPT, sizeof(PROMPT) - 1);
    }
}

static void parse_input(shell_t *state, char *input)
{
    btree_t *tree = gen_exec_tree(input);

    state->stop_command = 0;
    exec_tree(state, tree->root);
    btree_free(tree);
}

static str_t *handle_not_tty(void)
{
    char *input = NULL;
    size_t l_cap = 0;
    ssize_t l_size = 0;

    l_size = getline(&input, &l_cap, stdin);
    if (l_size == -1)
        return NULL;
    input[l_size - 1] = '\0';
    return str_create(input);
}

void read_input(shell_t *state)
{
    str_t *temp;
    while (!state->stop_shell) {
        if (!state->is_atty) {
            temp = handle_not_tty();
        } else {
            print_prompt(state);
            temp = stock_input();
        }
        if (temp == NULL)
            break;
        start_history(state, temp->data);
        parse_input(state, temp->data);
        free(temp);
    }
}
