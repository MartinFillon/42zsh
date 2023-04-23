/*
** EPITECH PROJECT, 2022
** int specifier test
** File description:
** tests for exec_utils
*/

#include <criterion/criterion.h>

#include "my_map.h"
#include "my_vec.h"

char **arg_to_tabl(vec_str_t *path);
char **env_to_tabl(map_t *env);
vec_str_t *path_to_vec(map_t *env);

Test(env_to_tabl, test_simple_env)
{
    char *expected[] = {
        "TOTO=TATA",
        "TITI=caca",
        "HELLO=world",
    };
    map_t *env = map_create(10);
    map_set(env, STR("HELLO"), str_create("world"));
    map_set(env, STR("TOTO"), str_create("TATA"));
    map_set(env, STR("TITI"), str_create("caca"));

    char **test = env_to_tabl(env);

    for (size_t i = 0; test[i]; ++i) {
        cr_assert_str_eq(
            expected[i], test[i], "Failed for: [%s] [%s]\n", expected[i],
            test[i]
        );
    }
}

Test(arg_to_tabl, test_simple_argv)
{
    char *expected[] = {
        "ls",
        "-la",
        "HELLO",
    };
    vec_str_t *av = str_split(STR("ls -la HELLO"), STR(" "));
    char **test = arg_to_tabl(av);

    for (size_t i = 0; test[i]; ++i) {
        cr_assert_str_eq(
            expected[i], test[i], "Failed for: [%s] [%s]\n", expected[i],
            test[i]
        );
    }
}

Test(path_to_vec, test_with_path)
{
    char *expected[] = {
        "/bin",
        "/test",
    };
    map_t *env = map_create(10);
    map_set(env, STR("PATH"), str_create("/bin:/test"));

    vec_str_t *test = path_to_vec(env);

    for (size_t i = 0; i < test->size; ++i) {
        cr_assert_str_eq(expected[i], str_tocstr(test->data[i]));
    }
}

Test(path_to_vec, test_without_path)
{
    char *expected[] = {
        "/bin",
        "/usr/bin",
    };
    map_t *env = map_create(10);
    map_set(env, STR("PATH"), NULL);

    vec_str_t *test = path_to_vec(env);

    for (size_t i = 0; i < test->size; ++i) {
        cr_assert_str_eq(expected[i], str_tocstr(test->data[i]));
    }
}
