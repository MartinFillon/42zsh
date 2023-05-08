/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** split args
*/

#include <stdio.h>
#include <stdlib.h>

#include "my_str.h"
#include "my_utils.h"

static int keep_arg_or_free(void *ptr)
{
    str_t *arg = *(str_t **)ptr;

    if (arg->length > 0) {
        return 1;
    } else {
        free(arg);
        return 0;
    }
}

static vec_str_t *filter_args_and_check_quotes(
    int _quote, int _dquote, str_t *line
)
{
    if (_quote || _dquote) {
        dprintf(2, "Unmatched '%c'.\n", _quote ? '\'' : '"');
        free(line);
        return NULL;
    }

    vec_str_t *split_ = str_split(line, (str_t *)(&(__str_temp_t){1, 2, "\0"}));
    vec_str_t *args_ = (vec_str_t *)vec_filter(split_, &keep_arg_or_free);
    my_vfree(2, line, split_);
    return args_;
}

vec_str_t *split_args(str_t *line)
{
    int _quote = 0, _dquote = 0;

    for (size_t i = 0; i < line->length; ++i) {
        if (i > 0 && line->data[i - 1] == '\\')
            continue;
        if (!_dquote && line->data[i] == '\'')
            _quote = !_quote;
        if (!_quote && line->data[i] == '"')
            _dquote = !_dquote;
        if ((line->data[i] == ' ' || line->data[i] == '\t') &&
            (!_quote && !_dquote))
            line->data[i] = '\0';
    }
    return filter_args_and_check_quotes(_quote, _dquote, line);
}
