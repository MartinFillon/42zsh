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
    #include "mysh/history.h"


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

typedef struct pipe_s {
    int is_active;

    int action;
    int fds[2];
    int pipe_fd;
    int pids[2];
} pipe_t;

typedef struct redirect_s {
    int is_active;

    int fd;
    int action;
} redirect_t;

typedef struct history_s {
    str_t *destination;
    vec_history_entry_t *entries;
} history_t;

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
    history_t *history;
} shell_t;

#endif /* MYSH_MYSH_ */
