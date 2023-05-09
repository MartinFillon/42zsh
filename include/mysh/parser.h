/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** parser
*/

#ifndef MYSH_PARSER_
    #define MYSH_PARSER_

    #include "my_btree.h"
    #include "my_utils.h"

// SYMBOLS

// sorted by priority
enum SYMBOL_TYPE {
    SEMICOLUMN,
    AND,
    OR,
    PIPE,
    LEFTSHIFT,
    LEFT,
    RIGHTSHIFT,
    RIGHT,
};

static const char UNUSED *SYMBOLS[] = {
    ";", "&&", "||", ">>",  ">", "|", "<<", "<", NULL,
};

int is_symbol(char *data);
char *find_symbol(char const *symbol, char *line_at);


typedef struct shell_s shell_t;

// TREE
btree_t *gen_exec_tree(char const *line, shell_t *state);


#endif /* MYSH_PARSER_ */
