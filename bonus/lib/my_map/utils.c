/*
** EPITECH PROJECT, 2022
** my_map
** File description:
** utils
*/

#include "my_str.h"

size_t map_hash_key(str_t const *key)
{
    size_t h = 0x811c9dc5U;

    for (size_t i = 0; i < key->length; ++i)
        h = (h ^ key->data[i]) * 0x01000193U;

    return h;
}
