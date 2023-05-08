/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-martin.saldinger
** File description:
** termios
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>

#include "my_str.h"
#include "mysh/termios.h"

static const char PROMPT[] = "\033[1;31m42zsh $>\033[0m ";

void print_prompt(str_t *input, size_t *pos)
{
    printf("\033[2K\r");
    printf("%s%s", PROMPT, input->data);
    printf("\033[%ldD", input->length - (*pos + 1));
    fflush(stdout);
}

static str_t *delete_manager(size_t *pos, str_t *input)
{
    str_t *pre_input;
    str_t *post_input;

    if (input->length <= 0)
            return input;
    if (*pos == input->length) {
        input->data[--input->length] = '\0';
    } else {
        if (input->length == 1)
            return input;
        pre_input = str_substr(input, 0, *pos);
        post_input = str_substr(input, *pos + 1, input->length - (*pos) - 1);
        str_sadd(&pre_input, post_input);
        input = str_dup(pre_input);
        free(post_input);
        free(pre_input);
    }
    (*pos)--;
    return input;
}

str_t *add_to_input(size_t *pos, str_t *input, char c)
{
    str_t *pre_input;
    str_t *post_input;

    if (c == 27)
            return input;
    if (*pos == input->length){
        if (c == 27)
            return input;
        str_cadd(&input, c);
    } else {
        pre_input = str_substr(input, 0, *pos + 1);
        post_input = str_substr(input, *pos + 1, input->length - (*pos) - 1);
        str_cadd(&pre_input, c);
        str_sadd(&pre_input, post_input);
        input = str_dup(pre_input);
        free(post_input);
        free(pre_input);
    }
    (*pos)++;
    return input;
}

str_t *manage_input(char c, bool *state, str_t *input, size_t *pos)
{
    switch (c) {
        case ENTER:
            *state = false;
            print_prompt(input, pos);
            break;
        case DELETE:
            input = delete_manager(pos, input);
            break;
        case ARROW:
            arrow_builtins(input, pos);
            break;
        case KILL:
            *state = false;
            return (str_t *) -1;
        default:
            input = add_to_input(pos, input, c);
            break;
    }
    print_prompt(input, pos);
    return input;
}

str_t *stock_input(int ignore)
{
    struct termios old_tio;
    struct termios new_tio;
    str_t *input = str_create("");
    bool state = true;
    int ignored = 0;

    printf("%s", PROMPT);
    setup_termios(&old_tio, &new_tio);
    while (state) {
        input = read_termios(input, ignore, &ignored, &state);
    }
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    return input;
}
