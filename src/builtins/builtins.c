/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** builtins
*/

#include "my_map.h"

#include "mysh/builtins.h"

map_t *builtins_create(void)
{
    map_t *cmd = map_create(30);

    map_set(cmd, STR("cd"), &builtin_chdir);
    map_set(cmd, STR("env"), &builtin_env);
    map_set(cmd, STR("setenv"), &builtin_setenv);
    map_set(cmd, STR("unsetenv"), &builtin_unsetenv);
    map_set(cmd, STR("set"), &builtin_set);
    map_set(cmd, STR("fg"), &builtin_fg);
    map_set(cmd, STR("jobs"), &builtin_jobs);
    map_set(cmd, STR("alias"), &builtin_alias);
    map_set(cmd, STR("unalias"), &builtin_unalias);
    map_set(cmd, STR("unset"), &builtin_unset);
    map_set(cmd, STR("history"), &builtin_history);
    map_set(cmd, STR("if"), &builtin_if);
    map_set(cmd, STR("foreach"), &builtin_foreach);

    return cmd;
}
