/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** symbols
*/

#include <stdlib.h>
#include <string.h>

#include "my_btree.h"
#include "my_cstr.h"

#include "mysh/parser.h"

static void parse_line(bnode_t **node, char *line, int *failed);

static int check_line(char const *symbol, char const *line)
{
    size_t len = strlen(line);

    if (strcmp(symbol, ";") == 0)
        return 0;
    for (size_t i = 0; i < len; i++)
        if (line[i] != ' ')
            return 0;
    return 1;
}

static int find_line(
    bnode_t **node, char const *symbol, char *line, int *failed
)
{
    char *symb = NULL;
    char *left = NULL;
    char *right = NULL;

    for (long i = strlen(line) - 1; i >= 0; --i) {
        if ((symb = find_symbol(symbol, line + i)) != NULL) {
            line[i] = '\0';
            (*node)->data = symb;
            left = strdup(line);
            right = strdup(line + i + strlen(symb));

            *failed |= check_line(symb, left) || check_line(symb, right);
            parse_line(&(*node)->left, left, failed);
            parse_line(&(*node)->right, right, failed);
            free(line);
            return 1;
        }
    }
    return 0;
}

static void parse_line(bnode_t **node, char *line, int *failed)
{
    *node = bnode_create();

    for (int i = 0; SYMBOLS[i]; ++i)
        if (find_line(node, SYMBOLS[i], line, failed))
            return;

    (*node)->data = line;
}

btree_t *gen_exec_tree(char const *line)
{
    btree_t *tree = btree_create(NULL);
    int failed = 0;

    parse_line(&tree->root, strdup(line), &failed);

    if (failed) {
        btree_free(tree);
        return NULL;
    }
    return tree;
}
