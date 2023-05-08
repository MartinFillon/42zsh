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
#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/exec.h"
#include "mysh/history.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"

static void parse_input(shell_t *state, char *input)
{
    btree_t *tree = gen_exec_tree(input);
    str_t *precmd = NULL;
    str_t *postcmd = NULL;

    state->stop_cmd = 0;
    state->cmd_pgid = -1;
    state->exec_cmd_in_bg = 0;
    remove_zombies(state);
    if ((postcmd = map_get(state->alias, STR("postcmd"))) != NULL)
        exec_wrapper(state, postcmd->data);
    exec_tree(state, tree->root);
    btree_free(tree);
    if ((precmd = map_get(state->alias, STR("precmd"))) != NULL)
        exec_wrapper(state, precmd->data);
}

static str_t *handle_not_tty(void)
{
    static char *input = NULL;
    static size_t l_cap = 0;
    ssize_t l_size = 0;

    if ((l_size = getline(&input, &l_cap, stdin)) < 0) {
        free(input);
        return NULL;
    }
    input[l_size - 1] = '\0';
    return str_create(input);
}

void read_input(shell_t *state)
{
    str_t *temp;
    int ignore;

    while (!state->stop_shell) {
        if (!state->is_atty) {
            temp = handle_not_tty();
        } else {
            ignore =
                atoi(((str_t *)map_get(state->vars, STR("ignoreof")))->data);
            temp = stock_input(ignore);
        }
        if (temp == NULL)
            break;

        history_append(temp->data, &state->history);
        parse_input(state, temp->data);
        free(temp);
    }
    save_history(&state->history);
}
