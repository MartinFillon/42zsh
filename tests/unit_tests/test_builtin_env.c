/*
** EPITECH PROJECT, 2022
** int specifier test
** File description:
** tests for builtin env
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "my_map.h"
#include "my_stdio.h"
#include "my_utils.h"
#include "my_vec.h"

int builtin_env(vec_str_t UNUSED *av, map_t *env);
int builtin_setenv(vec_str_t *av, map_t *env);
int builtin_unsetenv(vec_str_t *av, map_t *env);

Test(builtin_env, test_print_env, .init = cr_redirect_stdout)
{
    char expected[] = "TOTO=TATA\nTITI=caca\nHELLO=world\n";

    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));
    map_set(env, STR("TOTO"), str_create("TATA"));
    map_set(env, STR("TITI"), str_create("caca"));

    builtin_env(NULL, env);

    cr_assert_stdout_eq_str(expected);
}

Test(builtin_setenv, test_setenv)
{
    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));
    map_set(env, STR("TOTO"), str_create("TATA"));
    map_set(env, STR("TITI"), str_create("caca"));

    vec_str_t *av = str_split(STR("a VARIABLE CACA"), STR(" "));
    vec_str_t *av2 = str_split(STR("a VARIABLE2"), STR(" "));

    builtin_setenv(av, env);
    builtin_setenv(av2, env);

    cr_assert(str_eq(map_get(env, STR("VARIABLE")), STR("CACA")));
    cr_assert(str_eq(map_get(env, STR("VARIABLE2")), STR("")));
}

Test(builtin_unsetenv, test_unsetenv)
{
    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));
    map_set(env, STR("TOTO"), str_create("TATA"));
    map_set(env, STR("TITI"), str_create("caca"));

    vec_str_t *av = str_split(STR("a HELLO"), STR(" "));

    builtin_unsetenv(av, env);

    cr_assert(map_get(env, STR("HELLO")) == NULL);
}

Test(builtin_unsetenv, test_error_unsetenv, .init = cr_redirect_stderr)
{
    char expected[] = "unsetenv: Too few arguments.\n";
    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));

    vec_str_t *av = str_split(STR("test"), STR(" "));

    builtin_unsetenv(av, env);

    cr_assert_stderr_eq_str(expected);
}

Test(
    builtin_unsetenv, test_error_setenv_too_many_args,
    .init = cr_redirect_stderr
)
{
    char expected[] = "setenv: Too many arguments.\n";
    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));

    vec_str_t *av = str_split(STR("a HELLO CACA caca"), STR(" "));

    builtin_setenv(av, env);

    cr_assert_stderr_eq_str(expected);
}

Test(
    builtin_unsetenv, test_error_setenv_invalid_args, .init = cr_redirect_stderr
)
{
    char expected[] =
        "setenv: Variable name must contain alphanumeric characters.\n";
    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));

    vec_str_t *av = str_split(STR("test HELLO= CACA=a"), STR(" "));

    builtin_setenv(av, env);

    cr_assert_stderr_eq_str(expected);
}

Test(
    builtin_unsetenv, test_error_setenv_invalid_args_2,
    .init = cr_redirect_stderr
)
{
    char expected[] =
        "setenv: Variable name must contain alphanumeric characters.\n";
    map_t *env = map_create(10, NULL);
    map_set(env, STR("HELLO"), str_create("world"));

    vec_str_t *av = str_split(STR("test HELLO="), STR(" "));

    builtin_setenv(av, env);

    cr_assert_stderr_eq_str(expected);
}
