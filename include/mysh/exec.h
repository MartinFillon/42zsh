/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** exec declarations
*/

#ifndef MYSH_EXEC_H
    #define MYSH_EXEC_H

    #include "my_btree.h"
    #include "my_vec.h"
    #include "my_map.h"

    #include "mysh/mysh.h"


// PIPES
pipe_t *pipe_create(void);
void pipe_apply(shell_t *state);
void pipe_reset(pipe_t *pipe);
void pipe_close(pipe_t *pipe);
void pipe_chain(pipe_t *pipe);


// REDIRECT
redirect_t *redirect_create(void);
void redirect_apply(shell_t *state);
void redirect_reset(redirect_t *red);


// EXEC
void exec_tree(shell_t *state, bnode_t *node);
void exec_command(
    shell_t *state, int (*builtin)(vec_str_t *, shell_t *), vec_str_t *av
);
void exec_error(int status);


// CONVERSIONS
char **arg_to_tabl(vec_str_t *path);
char **env_to_tabl(map_t *env);
vec_str_t *path_to_vec(map_t *env);


#endif /* MYSH_EXEC_H */
