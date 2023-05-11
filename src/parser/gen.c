/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** symbols
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_btree.h"
#include "my_cstr.h"
#include "my_str.h"

#include "mysh/mysh.h"
#include "mysh/history.h"
#include "mysh/parser.h"

static void parse_line(bnode_t **node, char *line);

static void update_ignored(int *ignore, char tok)
{
    if (!ignore[1] && tok == '\'')
        ignore[0] = !ignore[0];
    if (!ignore[0] && tok == '"')
        ignore[1] = !ignore[1];
    if (!ignore[2] && tok == '`')
        ignore[2] = !ignore[2];
    if (ignore[0] || ignore[1] || ignore[2])
        return;
    if (!ignore[3] ? (tok == ')') : (tok == '('))
        ignore[3] = !ignore[3];
}

static int should_ignored(int *ignore)
{
    return (ignore[0] || ignore[1] || ignore[2] || ignore[3]);
}

static int find_line(bnode_t **node, char const *symbol, char *line)
{
    char *symb = NULL;
    int ignore[4] = {0};

    for (long i = strlen(line) - 1; i >= 0; --i) {
        symb = find_symbol(symbol, line + i);
        update_ignored(ignore, line[i]);
        if (i > 0 && line[i - 1] == '\\')
            continue;
        if (symb != NULL && !should_ignored(ignore)) {
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

btree_t *gen_exec_tree(char const *line, shell_t *state)
{
    btree_t *tree = btree_create(NULL);
    str_t *line_cpy = str_create(line);

    while (str_find(line_cpy, STR("!"), 0) != -1){
        if (get_exclamation(&line_cpy, state) == 1){
            tree->root = bnode_create();
            tree->root->data = strdup("");
            free(line_cpy);
            return tree;
        }
    }
    history_append(line_cpy->data, &state->history);
    parse_line(&tree->root, strdup(line_cpy->data));
    free(line_cpy);

    return tree;
}
