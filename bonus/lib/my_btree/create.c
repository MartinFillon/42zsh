/*
** EPITECH PROJECT, 2022
** my_btree
** File description:
** binary tree class
*/

#include <stdlib.h>

#include "my_btree.h"

bnode_t *bnode_create(void)
{
    bnode_t *new = malloc(sizeof(bnode_t));

    new->data = NULL;
    new->left = NULL;
    new->right = NULL;

    return new;
}

btree_t *btree_create(int (*cmp)(void *, void *))
{
    btree_t *new = malloc(sizeof(btree_t));

    new->root = NULL;
    new->size = 0;
    new->_cmp = cmp;

    return new;
}
