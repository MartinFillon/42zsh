/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** if
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "mysh/exec.h"
#include "mysh/history.h"
#include "mysh/mysh.h"
#include "mysh/parser.h"
#include "mysh/read.h"
#include "mysh/termios.h"
#include "my_btree.h"
#include "my_str.h"
#include "my_vec.h"

struct if_s {
    vec_str_t *commands_true;
    vec_str_t *commands_false;
    str_t *cond;
};

size_t parenthesis_case(vec_str_t *av, str_t **cond);
size_t get_condition(vec_str_t *av, str_t **cond);

static void get_then_commands(
    vec_str_t **commands_true, vec_str_t **commands_false, shell_t *state
)
{
    str_t *tmp = get_user_input(state, "if? ");

    while (str_eq(tmp, STR("else")) == 0 && str_eq(tmp, STR("endif")) == 0) {
        vec_pushback(commands_true, &tmp);
        tmp = get_user_input(state, "if? ");
    }
    if (str_eq(tmp, STR("else"))) {
        free(tmp);
        tmp = get_user_input(state, "if? ");
    }
    while (str_eq(tmp, STR("endif")) == 0) {
        vec_pushback(commands_false, &tmp);
        tmp = get_user_input(state, "if? ");
    }
    free(tmp);
}

static void one_line_if(struct if_s *commands, vec_str_t *av, size_t i)
{
    str_t *tmp = str_create("");

    for (; i < av->size; i++) {
        str_sadd(&tmp, av->data[i]);
        str_cadd(&tmp, ' ');
    }
    vec_pushback(&commands->commands_true, &tmp);
}

static int obtain_if_content(
    struct if_s *commands, shell_t *state, vec_str_t *av
)
{
    size_t i = 0;

    if (av->size < 2) {
        dprintf(2, "if: Too few arguments.\n");
        return 1;
    }
    i = get_condition(av, &commands->cond);
    if (i >= av->size) {
        dprintf(2, "if: Empty if.\n");
        return 1;
    }
    if (str_eq(av->data[i], STR("then")) && !state->is_atty) {
        get_then_commands(
            &commands->commands_true, &commands->commands_false, state);
    } else if (str_eq(av->data[i], STR("then")) && state->is_atty) {
        dprintf(2, "if: Improper then.\n");
        return 1;
    } else
        one_line_if(commands, av, i);
    return 0;
}

int builtin_if(vec_str_t *av, shell_t *state)
{
    struct if_s if_s = {
        vec_create(1, sizeof(str_t *)), vec_create(1, sizeof(str_t *)),
        str_create("test ")};

    if (obtain_if_content(&if_s, state, av) == 1)
        return 1;
    if (exec_sub_proc(state, if_s.cond) == 0) {
        for (size_t i = 0; i < if_s.commands_true->size; i++)
            exec_sub_proc(state, if_s.commands_true->data[i]);
        free(if_s.commands_true);
        vec_free(if_s.commands_false);
    } else {
        for (size_t i = 0; i < if_s.commands_false->size; i++)
            exec_sub_proc(state, if_s.commands_false->data[i]);
        free(if_s.commands_false);
        vec_free(if_s.commands_true);
    }
    return 0;
}
