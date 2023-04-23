/*
** EPITECH PROJECT, 2022
** my_btree
** File description:
** free a btree
*/

#include <stdlib.h>

#include "my_btree.h"

static void rec_helper(bnode_t *node)
{
    if (node == NULL)
        return;

    rec_helper(node->left);
    rec_helper(node->right);
    free(node->data);
    free(node);
}

void btree_free(btree_t *tree)
{
    rec_helper(tree->root);
    free(tree);
}
