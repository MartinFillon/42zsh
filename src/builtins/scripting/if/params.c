/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** params
*/

#include <stdbool.h>
#include <stddef.h>

#include "mysh/mysh.h"

size_t parenthesis_case(vec_str_t *av, str_t **cond)
{
    str_add(cond, av->data[1]->data + 1);
    str_cadd(cond, ' ');

    if (str_endswith(av->data[1], STR(")"))) {
        (*cond)->data[(*cond)->length - 2] = '\0';
        return 2;
    }
    for (size_t i = 2; i < av->size; i++) {
        if (str_endswith(av->data[i], STR(")"))) {
            av->data[i]->data[av->data[i]->length - 1] = '\0';
            str_sadd(cond, av->data[i]);
            return i + 1;
        }
        str_sadd(cond, av->data[i]);
        str_cadd(cond, ' ');
    }
    return av->size + 1;
}

size_t get_condition(vec_str_t *av, str_t **cond)
{
    if (str_eq(av->data[1], STR("1")) || str_eq(av->data[1], STR("0"))) {
        str_sadd(cond, av->data[1]);
        return 2;
    }
    if (str_startswith(av->data[1], STR("(")))
        return parenthesis_case(av, cond);
    else {
        str_sadd(cond, av->data[1]);
        str_cadd(cond, ' ');
        str_sadd(cond, av->data[2]);
        str_cadd(cond, ' ');
        str_sadd(cond, av->data[3]);
        return 4;
    }
}
