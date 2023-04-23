/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** middleware
*/

#ifndef MYSH_MIDDLEWARE_
    #define MYSH_MIDDLEWARE_

    #include "my_btree.h"
    #include "my_map.h"

    #include "mysh/mysh.h"


typedef void (*middleware_t)(shell_t *, bnode_t *);


char *trim_string(char *data);
map_t *middleware_create(void);
void pipe_middleware(shell_t *, bnode_t *);
void semicolumn_middleware(shell_t *, bnode_t *);
void exec_if_fail_middleware(shell_t *, bnode_t *);
void exec_if_success_middleware(shell_t *, bnode_t *);
void append_file_middleware(shell_t *, bnode_t *);
void write_file_middleware(shell_t *, bnode_t *);
void read_file_middleware(shell_t *, bnode_t *);
void heredoc_middleware(shell_t *, bnode_t *);


#endif /* MYSH_MIDDLEWARE_ */
