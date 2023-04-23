/*
** EPITECH PROJECT, 2022
** my_map
** File description:
** setters
*/

#include <stdlib.h>

#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

static int overwrite_in_vector(
    vec_map_elem_t *cands, str_t const *key, void *data
)
{
    if (cands->size == 0)
        return 0;

    for (size_t i = 0; i < cands->size; ++i) {
        if (str_eq(cands->data[i].key, key)) {
            cands->data[i].data = data;
            return 1;
        }
    }
    return 0;
}

void map_set(map_t *map, str_t const *key, void *data)
{
    size_t idx = map_hash_key(key) % map->capacity;

    if (map->elems->data[idx] == NULL) {
        vec_map_elem_t *tmp = vec_create(20, sizeof(map_elem_t));
        vec_insert(&map->elems, &tmp, idx);
    }

    if (overwrite_in_vector(map->elems->data[idx], key, data))
        return;

    vec_pushback(&map->elems->data[idx], &(map_elem_t){str_dup(key), data});
}
