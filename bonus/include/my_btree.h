/*
** EPITECH PROJECT, 2022
** my_btree
** File description:
** btree
*/

#ifndef INCLUDE_MY_BTREE_
    #define INCLUDE_MY_BTREE_
    #include <stddef.h>

    #define IS_END(n) ((n)->left == NULL && (n)->right == NULL)

typedef struct bnode_s {
    void *data;
    struct bnode_s *left;
    struct bnode_s *right;
} bnode_t;

typedef struct btree_s {
    bnode_t *root;
    size_t size;
    int (*_cmp)(void *, void *);
} btree_t;

/**
 * @brief creates a new btree
 *
 * @param cmp  the comparison function used to insert the data
 *
 * @return a new btree
 */
btree_t *btree_create(int (*cmp)(void *, void *));

/**
 * @brief frees a btree
 *
 * @param tree  the btree to free
 */
void btree_free(btree_t *tree);

/**
 * @brief creates a new btree node
 *
 * @return a new btree node
 */
bnode_t *bnode_create(void);

/**
 * @brief inserts a new element in a btree
 *
 * @param root  the root of the btree
 * @param data  the data to insert
 */
void btree_insert(btree_t *tree, void *data);

/**
 * @brief searches for an element in a btree
 *
 * @param root  the root of the btree
 * @param data  the data to search for
 * @return the data if found, NULL otherwise
 */
void *btree_find(btree_t *root, void *data);

#endif /* INCLUDE_MY_BTREE_ */
