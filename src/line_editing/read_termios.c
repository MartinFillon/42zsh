/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** read input
*/

#include <stdio.h>
#include <stdlib.h>

#include "my_str.h"

#include "mysh/termios.h"

static bool handle_ignoreeof(shell_input_t *in, str_t *ign_, long ignoreeof)
{
    bool ign_unset = ign_ == NULL;
    bool should_print_warning =
        !ign_unset && (str_eq(ign_, STR("0")) || ign_->length == 0);

    if (should_print_warning && in->input == NULL)
        return false;

    if ((ign_unset || should_print_warning) || ignoreeof <= 0)
        return true;
    return false;
}

void read_termios(char const *prompt, shell_t *state, shell_input_t *in)
{
    char c = 0;
    str_t *ignore = map_get(state->vars, STR("ignoreeof"));
    long ignoreeof = (ignore != NULL) ? str_toint(ignore) : 0;

    while (read(STDIN_FILENO, &c, 1) > 0) {
        if (manage_input(prompt, c, in, state) == false)
            continue;
        ignoreeof--;
        if (handle_ignoreeof(in, ignore, ignoreeof) == false) {
            in->input = str_create("");
            printf("^D\nUse \"exit\" to leave.\n");
            print_prompt(prompt, in);
        } else {
            return;
        }
    }
}
