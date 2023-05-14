/*
** EPITECH PROJECT, 2022
** my_map
** File description:
** getters
*/

#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

void *map_get(map_t const *map, str_t const *key)
{
    size_t idx = map_hash_key(key) % map->capacity;
    vec_map_elem_t *cands = map->elems->data[idx];

    if (cands == NULL || cands->size == 0)
        return NULL;

    for (size_t i = 0; i < cands->size; ++i)
        if (str_eq(cands->data[i].key, key))
            return cands->data[i].data;

    return NULL;
}

vec_str_t *map_get_keys(map_t const *map)
{
    vec_str_t *keys = vec_create(map->capacity, sizeof(str_t *));
    vec_map_elem_t *col = NULL;

    for (size_t i = 0; i < map->capacity; i++) {
        col = map->elems->data[i];
        if (col == NULL || col->size == 0)
            continue;
        for (size_t j = 0; j < col->size; j++)
            vec_pushback(&keys, &(str_t *){str_dup(col->data[j].key)});
    }
    return keys;
}
