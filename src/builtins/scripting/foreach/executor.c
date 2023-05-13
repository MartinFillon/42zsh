/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** executor
*/

#include <ctype.h>
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

static const char PROMPT[] = "\033[1;32mforeach?\033[0m ";

static int exec_commands(shell_t *state)
{
    btree_t *tree = NULL;
    char *prompt = strdup(PROMPT);
    str_t *tmp = get_user_input(state, prompt);

    str_println(tmp);
    while (tmp && str_eq(tmp, STR("end")) == false) {
        tree = gen_exec_tree(tmp->data, state);
        exec_tree(state, tree->root);
        btree_free(tree);
        free(tmp);
        tmp = get_user_input(state, prompt);
        str_println(tmp);
    }
    if (tmp == NULL) {
        dprintf(2, "foreach: end not found.\n");
        return 1;
    }
    my_vfree(2, prompt, tmp);
    return 0;
}

static void exec_piped_foreach(
    vec_str_t *list, shell_t *state, vec_str_t *commands, str_t *var
)
{
    btree_t *tree = NULL;

    for (size_t i = 0; i < list->size; i++) {
        if (map_get(state->vars, var) != NULL)
            free(map_get(state->vars, var));
        map_set(state->vars, var, list->data[i]);
        for (size_t j = 0; j < commands->size; j++) {
            tree = gen_exec_tree(commands->data[j]->data, state);
            exec_tree(state, tree->root);
            btree_free(tree);
        }
    }
}

int piped_foreach(shell_t *state, str_t *var, vec_str_t *list)
{
    vec_str_t *commands = vec_create(10, sizeof(str_t *));
    str_t *tmp = get_user_input(state, STR("foreach? ")->data);

    while (tmp && str_eq(tmp, STR("end")) == false) {
        vec_pushback(&commands, &tmp);
        tmp = get_user_input(state, STR("foreach? ")->data);
    }
    if (tmp == NULL) {
        dprintf(2, "foreach: end not found.\n");
        return 1;
    }
    exec_piped_foreach(list, state, commands, var);
    my_vfree(3, var, list, tmp);
    vec_free(commands);
    return 0;
}

int script_foreach(shell_t *state, str_t *var, vec_str_t *list, long int offset)
{
    for (size_t i = 0; i < list->size; i++) {
        setbuf(stdin, NULL);
        fseek(stdin, offset, SEEK_SET);
        if (map_get(state->vars, var) != NULL)
            free(map_get(state->vars, var));
        map_set(state->vars, var, list->data[i]);
        if (exec_commands(state))
            return 1;
    }
    my_vfree(2, var, list);
    return 0;
}
