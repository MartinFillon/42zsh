/*
** EPITECH PROJECT, 2022
** my_map
** File description:
** map implementation
*/

#include <stdlib.h>
#include <string.h>

#include "my_map.h"

map_t *map_create(size_t capacity)
{
    map_t *map = malloc(sizeof(map_t));

    if (map == NULL)
        return NULL;

    map->capacity = capacity;
    map->elems = vec_create(capacity, sizeof(vec_map_elem_t *));
    memset(map->elems->data, 0, sizeof(vec_map_elem_t *) * map->capacity);

    return map;
}
