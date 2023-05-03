/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** builtins declarations
*/

#ifndef MYSH_BUILTINS_H
    #define MYSH_BUILTINS_H

    #include"my_map.h"


map_t *builtins_create(void);

int builtin_env(vec_str_t *av, map_t *env);

int builtin_chdir(vec_str_t *av, map_t *env);

int builtin_setenv(vec_str_t *av, map_t *env);

int builtin_unsetenv(vec_str_t *av, map_t *env);

int builtin_history(vec_str_t *av, map_t *env);

#endif /* MYSH_BUILTINS_H */
