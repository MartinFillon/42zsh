/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** semicolumn
*/

#include "my_btree.h"

#include "mysh/exec.h"
#include "mysh/mysh.h"

void semicolumn_middleware(shell_t *state, bnode_t *node)
{
    exec_tree(state, node->left);
    exec_tree(state, node->right);
}
