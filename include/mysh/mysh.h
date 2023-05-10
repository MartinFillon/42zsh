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

    #define EQUAL 1
    #define NOT_EQUAL 0


typedef int fd_set_t[2];

VEC_DEF(fd_set_t, fd)

typedef struct job_s {
    pid_t pgid;
    str_t *cmd;
} job_t;

VEC_DEF(job_t, job)
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

typedef struct pipe_s {
    int is_active;

    pid_t pgid;
    int action;
    int fds[2];
    int pipe_fd;
    int first_pid;
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
    int stop_cmd;
    int is_atty;
    pid_t shell_pgid;
    pid_t cmd_pgid;
    int exec_cmd_in_bg;

    redirect_t redirect;
    pipe_t pipe;
    map_t *vars;
    vec_job_t *jobs;
    map_t *alias;
    history_t history;
} shell_t;

#endif /* MYSH_MYSH_ */
