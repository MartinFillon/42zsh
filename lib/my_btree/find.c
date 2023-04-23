/*
** EPITECH PROJECT, 2022
** my_btree
** File description:
** find
*/

#include "my_btree.h"

static void *rec_helper(bnode_t *node, void *data, int (*cmp)(void *, void *))
{
    if (node == NULL)
        return NULL;

    int comp = cmp(node->data, data);

    if (comp == 0)
        return node->data;

    if (comp < 0) {
        return rec_helper(node->right, data, cmp);
    } else {
        return rec_helper(node->left, data, cmp);
    }
}

void *btree_find(btree_t *tree, void *data)
{
    return rec_helper(tree->root, data, tree->_cmp);
}
