/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** foreach
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
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"

static const char PROMPT[] = "\033[1;32mforeach?\033[0m ";

static vec_str_t *get_commands(shell_t *state)
{
    vec_str_t *commands = vec_create(10, sizeof(str_t *));
    char *prompt = strdup(PROMPT);
    str_t *tmp = NULL;

    tmp = get_user_input(state, prompt);
    if (tmp == NULL) {
        dprintf(2, "foreach: end not found.\n");
        return NULL;
    }
    while (str_compare(tmp, STR("end")) != 0) {
        vec_pushback(&commands, &tmp);
        tmp = get_user_input(state, prompt);
        if (tmp == NULL) {
            dprintf(2, "foreach: end not found.\n");
            return NULL;
        }
    }
    free(prompt);
    return commands;
}

static str_t *get_var_name(str_t *line)
{
    str_t *var = str_create("");
    long i = STR("foreach")->length + 1;

    while (isalpha(line->data[i]) && line->data[i]) {
        str_cadd(&var, line->data[i]);
        i++;
    }

    return var;
}

static vec_str_t *get_arg_list(str_t *line)
{
    long start = str_find(line, STR("("), 0) + 1;
    long end = str_find(line, STR(")"), 0);

    if (start == -1 || end == -1 || start >= end)
        return NULL;

    str_t *tmp = str_substr(line, start, end - start);
    vec_str_t *list = str_split(tmp, STR(" "));
    free(tmp);
    return list;
}

static void exec_commands(shell_t *state, vec_str_t *commands)
{
    btree_t *tree = NULL;

    for (size_t i = 0; i < commands->size; i++) {
        tree = gen_exec_tree(commands->data[i]->data, state);
        exec_tree(state, tree->root);
        btree_free(tree);
    }
}

int builtin_foreach(vec_str_t *av, shell_t *state)
{
    vec_str_t *commands = get_commands(state);
    str_t *tmp = str_join(av, STR(" "));
    str_t *var = get_var_name(tmp);
    vec_str_t *list = get_arg_list(tmp);
    free(tmp);
    if (list == NULL || commands == NULL) {
        free(var);
        return 1;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (map_get(state->vars, var) != NULL)
            free(map_get(state->vars, var));
        map_set(state->vars, var, list->data[i]);
        exec_commands(state, commands);
        map_del(state->vars, var);
    }
    vec_free(commands);
    free(var);
    return 0;
}
