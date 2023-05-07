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

static void parse_line(bnode_t **node, char *line);

static int find_line(bnode_t **node, char const *symbol, char *line)
{
    char *symb = NULL;

    for (long i = strlen(line) - 1; i >= 0; --i) {
        symb = find_symbol(symbol, line + i);
        if (i > 0 && line[i - 1] == '\\')
            continue;
        if (symb != NULL) {
            line[i] = '\0';
            (*node)->data = symb;
            parse_line(&(*node)->left, strdup(line));
            parse_line(&(*node)->right, strdup(line + i + strlen(symb)));
            free(line);
            return 1;
        }
    }
    return 0;
}

static void parse_line(bnode_t **node, char *line)
{
    *node = bnode_create();

    for (int i = 0; SYMBOLS[i]; ++i)
        if (find_line(node, SYMBOLS[i], line))
            return;

    (*node)->data = line;
}

btree_t *gen_exec_tree(char const *line)
{
    btree_t *tree = btree_create(NULL);

    parse_line(&tree->root, strdup(line));

    return tree;
}
