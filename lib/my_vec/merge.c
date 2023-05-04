/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** merge
*/

#include <stdio.h>
#include <string.h>
#include "my_vec.h"
void vec_merge(void *dest, void *src)
{
    vec_t **dest_ = (vec_t **)dest;
    vec_t *src_ = (vec_t *)src;

    if ((*dest_)->_elem_size != src_->_elem_size)
        return;

    if ((*dest_)->size + src_->size >= (*dest_)->capacity)
        vec_resize(dest_, (*dest_)->size + src_->size);

    memcpy(vec_at(*dest_, (*dest_)->size), src_->data, src_->size * src_->_elem_size);
    (*dest_)->size += src_->size;
}
