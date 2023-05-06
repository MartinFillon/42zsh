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

VEC_DEF(pid_t, pid)

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

    pid_t pgid;
    int action;
    int fds[2];
    int pipe_fd;
    int first_pid;
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
    int stop_cmd;
    int is_atty;
    pid_t shell_pgid;
    pid_t cmd_pgid;
    int exec_cmd_in_bg;

    redirect_t redirect;
    pipe_t pipe;
    map_t *vars;
    vec_pid_t *jobs;
} shell_t;

#endif /* MYSH_MYSH_ */
