/*
** EPITECH PROJECT, 2022
** mysh
** File description:
** utils
*/

#include <stdlib.h>

#include "my_map.h"
#include "my_vec.h"

char **arg_to_tabl(vec_str_t *path)
{
    char **ar = malloc(sizeof(char *) * (path->size + 1));
    ar[path->size] = NULL;

    for (size_t i = 0; i < path->size; ++i)
        ar[i] = (char *)str_tocstr(path->data[i]);

    return ar;
}

char **env_to_tabl(map_t *env)
{
    vec_str_t *keys = map_get_keys(env);
    char **ev = malloc(sizeof(char *) * (keys->size + 1));
    ev[keys->size] = NULL;
    str_t *temp = NULL;

    for (size_t i = 0; i < keys->size; ++i) {
        temp = map_get(env, keys->data[i]);
        ev[i] =
            malloc(sizeof(char) * (keys->data[i]->length + temp->length + 2));
        ev[i][0] = 0;
        strncat(ev[i], keys->data[i]->data, keys->data[i]->length);
        strcat(ev[i], "=");
        strncat(ev[i], temp->data, temp->length);
    }
    vec_free(keys);
    return ev;
}

vec_str_t *path_to_vec(map_t *env)
{
    str_t *path_ = map_get(env, STR("PATH"));

    vec_str_t *path =
        str_split((path_ == NULL) ? STR("/bin:/usr/bin") : path_, STR(":"));

    return path;
}
