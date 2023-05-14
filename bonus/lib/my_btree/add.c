/*
** EPITECH PROJECT, 2022
** my_btree
** File description:
** insert
*/

#include "my_btree.h"

static void rec_helper(bnode_t **node, void *data, int (*cmp)(void *, void *))
{
    if (*node == NULL) {
        *node = bnode_create();
        (*node)->data = data;
        return;
    }

    if (cmp((*node)->data, data) <= 0) {
        rec_helper(&(*node)->right, data, cmp);
    } else {
        rec_helper(&(*node)->left, data, cmp);
    }
}

void btree_insert(btree_t *tree, void *data)
{
    rec_helper(&tree->root, data, tree->_cmp);
    tree->size++;
}
