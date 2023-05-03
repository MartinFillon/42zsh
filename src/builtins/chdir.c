/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** chdir
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>

#include "my_map.h"
#include "my_str.h"

#include "mysh/mysh.h"

static char const *get_homepath(map_t *env)
{
    str_t *path = NULL;

    if ((path = map_get(env, STR("HOME"))) != NULL)
        return str_tocstr(path);

    dprintf(2, "cd: No home directory.\n");
    return NULL;
}

static char const *get_dirpath(str_t *p_, map_t *env)
{
    str_t *path = NULL;

    if (str_eq(p_, STR("-"))) {
        if ((path = map_get(env, STR("OLDPWD"))) != NULL)
            return str_tocstr(path);

        dprintf(2, ": No such file or directory.\n");
        return NULL;
    }
    return str_tocstr(p_);
}

void update_pwd(shell_t *state)
{
    static char PATHNAME[MAXPATHLEN] = "";
    str_t *old = map_get(state->env, STR("OLDPWD"));
    str_t *curr = map_get(state->env, STR("PWD"));
    str_t *cwd = map_get(state->vars, STR("cwd"));

    if (old == NULL) {
        old = str_create("");
        map_set(state->env, STR("OLDPWD"), old);
    }
    if (curr == NULL) {
        curr = str_create("");
        map_set(state->env, STR("PWD"), curr);
    }

    str_sadd(str_clear(&old), curr);
    str_add(str_clear(&curr), getcwd(PATHNAME, MAXPATHLEN));
    str_sadd(str_clear(&cwd), curr);
}

static void perror_wrapper(char const *path)
{
    char *error = strerror(errno);

    dprintf(2, "%s: %s.\n", path, error);
}

int builtin_chdir(vec_str_t *av, shell_t *state)
{
    char const *path = NULL;
    int success;

    if (av->size > 2) {
        dprintf(2, "cd: Too many arguments.\n");
        return 1;
    }
    if ((av->size == 1 && (path = get_homepath(state->env)) == NULL) ||
        (av->size == 2 && (path = get_dirpath(av->data[1], state->env)) == NULL
        )) {
        return 1;
    }
    success = chdir(path) != 0;
    (success) ? perror_wrapper(path) : update_pwd(state);
    return success;
}
