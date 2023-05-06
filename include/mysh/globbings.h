/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** globbins
*/

#ifndef GLOBBINS_H_
    #define GLOBBINS_H_
    #include "my_str.h"

vec_str_t *question_mark_handler(str_t *word);
vec_str_t *get_wildcard_matches(str_t *pattern);

#endif /* !GLOBBINS_H_ */
