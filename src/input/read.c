/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** read
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_btree.h"
#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

#include "mysh/mysh.h"
#include "mysh/exec.h"
#include "mysh/history.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"

void parse_input(shell_t *state, char *input)
{
    btree_t *tree = gen_exec_tree(input, state);
    str_t *cmd = NULL;

    state->stop_cmd = 0;
    state->cmd_pgid = -1;
    state->exec_cmd_in_bg = 0;
    remove_zombies(state);
    if ((cmd = map_get(state->alias, STR("postcmd"))) != NULL)
        exec_wrapper(state, cmd->data);
    exec_tree(state, tree->root);
    btree_free(tree);
    if ((cmd = map_get(state->alias, STR("precmd"))) != NULL)
        exec_wrapper(state, cmd->data);
}

static str_t *handle_no_tty(void)
{
    static char *input = NULL;
    static size_t l_cap = 0;
    ssize_t l_size = 0;

    if ((l_size = getline(&input, &l_cap, stdin)) < 0) {
        free(input);
        return NULL;
    }
    input[l_size - 1] = '\0';
    if (input[0] == '\0')
        return NULL;
    return str_create(input);
}

str_t *get_user_input(shell_t *state, char const *prompt)
{
    if (state->is_atty)
        return handle_line_editing(state, prompt);
    return handle_no_tty();
}

static void update_return_code(shell_t *state)
{
    if (map_get(state->vars, STR("?")) != NULL)
        free(map_get(state->vars, STR("?")));

    map_set(state->vars, STR("?"), my_itostr(state->return_code));
}

void shell_loop(shell_t *state)
{
    str_t *temp = NULL;
    char const *prompt;

    while (!state->stop_shell) {
        prompt = str_tocstr(map_get(state->vars, STR("prompt")));
        update_return_code(state);
        if ((temp = get_user_input(state, prompt)) == NULL)
            break;
        parse_input(state, temp->data);
        free(temp);
    }
}
