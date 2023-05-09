/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** builtins declarations
*/

#ifndef MYSH_BUILTINS_H
    #define MYSH_BUILTINS_H

    #include"my_map.h"

    #include "mysh/mysh.h"

map_t *builtins_create(void);

map_t *vars_create(map_t *);

int builtin_env(vec_str_t *, shell_t *);

int builtin_chdir(vec_str_t *, shell_t *);

int builtin_setenv(vec_str_t *, shell_t *);

int builtin_unsetenv(vec_str_t *, shell_t *);

int builtin_set(vec_str_t *, shell_t *);

int builtin_fg(vec_str_t *, shell_t *);

int builtin_jobs(vec_str_t *, shell_t *);

int builtin_fg(vec_str_t *, shell_t *);

int builtin_jobs(vec_str_t *, shell_t *);

int builtin_alias(vec_str_t *, shell_t *);

int builtin_unalias(vec_str_t *, shell_t *);

int builtin_unset(vec_str_t *, shell_t *);

int builtin_history(vec_str_t *, shell_t *);

int builtin_if(vec_str_t *, shell_t *);

int builtin_foreach(vec_str_t *, shell_t *);

int builtin_foreach(vec_str_t *, shell_t *);

int builtin_where(vec_str_t *, shell_t *);

int builtin_which(vec_str_t *, shell_t *);
#endif /* MYSH_BUILTINS_H */
