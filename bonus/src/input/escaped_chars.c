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
        *_quote = !*_quote;
    if (arg->data[*i] == '"')
        *_dquote = !*_dquote;
    if ((arg->data[*i] == '\'' && !*_dquote) ||
        (arg->data[*i] == '"' && !*_quote)) {
        str_erase_at_idx(&arg, *i);
    } else {
        ++*i;
    }
}

static void replace_escaped_char(char *chr)
{
    switch (*chr) {
        case 'n': *chr = '\n'; break;
        case 't': *chr = '\t'; break;
        case 'r': *chr = '\r'; break;
        case '"': *chr = '\"'; break;
        case '`': *chr = '`'; break;
        case '\'': *chr = '\''; break;
        case '\\': *chr = '\\'; break;
    };
}

void remove_escaped_chars_and_quotes(str_t *arg)
{
    int quotes[2] = {0, 0};
    size_t i = 0;

    if (arg->data[i] == '\\')
        i++;
    while (i < arg->length) {
        if (arg->data[i] != '\\') {
            remove_quotes(arg, quotes, &i);
            continue;
        }
        if (quotes[0] || quotes[1]) {
            i++;
            continue;
        }
        str_erase_at_idx(&arg, i);
        replace_escaped_char(&arg->data[i]);
        i++;
    }
}
