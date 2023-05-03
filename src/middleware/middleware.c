/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** middleware for symbols
*/

#include "my_map.h"

#include "mysh/exec.h"
#include "mysh/middleware.h"
#include "mysh/parser.h"

map_t *middleware_create(void)
{
    map_t *middleware = map_create(10);

    map_set(middleware, STR(";"), &semicolumn_middleware);
    map_set(middleware, STR("|"), &pipe_middleware);
    map_set(middleware, STR("||"), &exec_if_fail_middleware);
    map_set(middleware, STR("&&"), &exec_if_success_middleware);
    map_set(middleware, STR(">"), &write_file_middleware);
    map_set(middleware, STR(">>"), &append_file_middleware);
    map_set(middleware, STR("<"), &read_file_middleware);
    map_set(middleware, STR("<<"), &heredoc_middleware);
    map_set(middleware, STR("="), &export_variable_middleware);

    return middleware;
}
