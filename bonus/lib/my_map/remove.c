/*
** EPITECH PROJECT, 2022
** my_map
** File description:
** remove elem from map
*/

#include <stdlib.h>

#include "my_map.h"
#include "my_str.h"
#include "my_vec.h"

void map_del(map_t *map, str_t const *key)
{
    size_t idx = map_hash_key(key) % map->capacity;
    vec_map_elem_t *cands = map->elems->data[idx];

    if (cands == NULL || cands->size == 0)
        return;

    for (size_t i = 0; i < cands->size; ++i) {
        if (str_eq(cands->data[i].key, key)) {
            free(cands->data[i].key);
            vec_remove(cands, i);
            return;
        }
    }
}
