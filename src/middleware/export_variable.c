/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** export_variable
*/

#include "my_btree.h"
#include "my_map.h"
#include "my_str.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"

void export_variable(shell_t *state, bnode_t *node)
{
    char const *key = node->left->data;
    char *value = node->right->data;
    map_set(state->vars, str_create(key), value);
}
