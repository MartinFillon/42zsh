/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** foreach
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysh/exec.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"
#include "my_btree.h"
#include "my_str.h"
#include "my_vec.h"

static const char PROMPT[] = "\033[1;32mforeach?\033[0m ";

static vec_str_t *get_commands(shell_t *state)
{
    vec_str_t *commands = vec_create(10, sizeof(str_t *));
    char *prompt = strdup(PROMPT);
    str_t *tmp = NULL;

    tmp = handle_line_editing(state, prompt);
    if (tmp == NULL) {
        dprintf(2, "foreach: end not found.\n");
        return (NULL);
    }
    while (str_compare(tmp, STR("end")) != 0) {
        vec_pushback(&commands, &tmp);
        tmp = handle_line_editing(state, prompt);
        if (tmp == NULL) {
            dprintf(2, "foreach: end not found.\n");
            return (NULL);
        }
    }
    free(prompt);
    return (commands);
}

static void get_word(bool *var_end, str_t *w, str_t **tmp, str_t **var)
{
    for (size_t k = 0; k < w->length; k++) {
        if (w->data[k] == '{') {
            *var_end = 1;
            continue;
        }
        if (w->data[k] == '}' || w->data[k] == ' ')
            continue;
        str_cadd((*var_end) ? var : tmp, w->data[k]);
    }
}

static vec_str_t *get_list(vec_str_t *av, str_t **var)
{
    bool var_end = 0;
    str_t *tmp = str_create("");
    vec_str_t *list = vec_create(100, sizeof(str_t *));

    for (size_t i = 1; i < av->size; ++i) {
        get_word(&var_end, av->data[i], &tmp, var);
        if (var_end && str_compare(tmp, STR(" ")) != 0) {
            vec_pushback(&list, &tmp);
            tmp = str_create("");
        }
    }
    return list;
}

int builtin_foreach(vec_str_t *av, shell_t *state)
{
    vec_str_t *commands = get_commands(state);
    str_t *var = str_create("");
    vec_str_t *list = get_list(av, &var);
    btree_t *tree = NULL;

    if (commands == NULL)
        return (1);
    for (size_t i = 0; i < list->size; i++) {
        map_set(state->vars, var, list->data[i]);
        for (size_t i = 0; i < commands->size; i++) {
            tree = gen_exec_tree(commands->data[i]->data, state);
            exec_tree(state, tree->root);
            btree_free(tree);
        }
    }
    vec_free(commands);
    return (0);
}
