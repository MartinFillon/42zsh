/*
** EPITECH PROJECT, 2022
** my_map
** File description:
** map free
*/

#include <stdlib.h>

#include "my_map.h"
#include "my_vec.h"

static void map_free_col(vec_map_elem_t *col, void (*free_fn)(void *))
{
    for (size_t i = 0; i < col->size; ++i) {
        if (free_fn != NULL)
            free_fn(col->data[i].data);
        free(col->data[i].key);
    }
    free(col);
}

void map_free(map_t *map, void (*free_fn)(void *))
{
    vec_map_elem_t *col = NULL;

    for (size_t i = 0; i < map->capacity; ++i) {
        col = map->elems->data[i];
        if (col == NULL)
            continue;
        map_free_col(col, free_fn);
    }
    free(map->elems);
    free(map);
}
