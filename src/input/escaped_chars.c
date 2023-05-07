/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** remove escaped chars
*/

#include "my_str.h"

static void remove_quotes(str_t *arg, int *quotes, size_t *i)
{
    int *_quote = &quotes[0];
    int *_dquote = &quotes[1];

    if (arg->data[*i] == '\'')
        *_dquote = !*_quote;
    if (arg->data[*i] == '"')
        *_dquote = !*_dquote;
    if ((arg->data[*i] == '\'' && !*_dquote) ||
        (arg->data[*i] == '"' && !*_quote)) {
        str_erase_at_idx(&arg, *i);
    } else {
        ++*i;
    }
}

void remove_escaped_chars_and_quotes(str_t *arg)
{
    int quotes[2] = {0, 0};

    size_t i = 0;
    while (i < arg->length) {
        if (arg->data[i] != '\\') {
            remove_quotes(arg, quotes, &i);
            continue;
        }
        str_erase_at_idx(&arg, i);
        switch (arg->data[i]) {
            case 'n': arg->data[i] = '\n'; break;
            case 't': arg->data[i] = '\t'; break;
            case 'r': arg->data[i] = '\r'; break;
            case '"': arg->data[i] = '\"'; break;
            case '\'': arg->data[i] = '\''; break;
            case '\\': arg->data[i++] = '\\'; break;
        };
        i++;
    }
}
