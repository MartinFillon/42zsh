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
    map_t *cmd = map_create(10);

    map_set(cmd, STR("cd"), &builtin_chdir);
    map_set(cmd, STR("env"), &builtin_env);
    map_set(cmd, STR("setenv"), &builtin_setenv);
    map_set(cmd, STR("unsetenv"), &builtin_unsetenv);
    map_set(cmd, STR("history"), &builtin_history);

    return cmd;
}
