/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** read
*/

#include <stdio.h>
#include <stdlib.h>

#include "my_btree.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"

const char PROMPT[] = "TamaShell $> ";

static void print_prompt(shell_t *state)
{
    if (state->is_atty) {
        write(1, PROMPT, sizeof(PROMPT) - 1);
    }
}

static void parse_input(shell_t *state, char *input)
{
    btree_t *tree = gen_exec_tree(input);

    if (tree == NULL) {
        dprintf(2, "Invalid null command.\n");
        state->return_code = 1;
        return;
    }
    exec_tree(state, tree->root);
    btree_free(tree);
}

void read_input(shell_t *state)
{
    str_t *temp;
    while (!state->stop) {
        print_prompt(state);
        temp = stock_input();
        parse_input(state, temp->data);
    }
}
