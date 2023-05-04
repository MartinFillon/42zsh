/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** main declarations
*/

#ifndef MYSH_MYSH_
    #define MYSH_MYSH_

    #include <unistd.h>

    #include "my_map.h"


typedef int fd_set_t[2];

VEC_DEF(fd_set_t, fd)

enum {
    READ,
    WRITE,
    READ_WRITE,
    CREATE,
    APPEND,
    SAVE,
    RESTORE
};

typedef struct {
    int is_active;

    int action;
    int fds[2];
    int pipe_fd;
    int pids[2];
} pipe_t;

typedef struct {
    int is_active;

    int fd;
    int action;
} redirect_t;


typedef struct shell_s {
    map_t *env;
    map_t *builtins;
    map_t *middlewares;
    int return_code;
    int stop_shell;
    int stop_command;
    int is_atty;

    redirect_t *redirect;
    pipe_t *pipe;
    map_t *vars;
    map_t *alias;
} shell_t;

#endif /* MYSH_MYSH_ */
