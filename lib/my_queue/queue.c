/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** queue utils
*/

#include <stdlib.h>

#include "my_queue.h"
#include "my_vec.h"

void queue_free(queue_t *queue)
{
    free(queue->_items);
    free(queue);
}

void queue_clear(queue_t *queue)
{
    vec_clear(queue->_items);
    queue->_start = 0;
    queue->is_empty = 1;
}

queue_t *queue_create(size_t initial_size)
{
    queue_t *queue = malloc(sizeof(queue_t));

    queue->_items = vec_create(initial_size, sizeof(int));
    queue->_start = 0;
    queue->is_empty = 1;

    return queue;
}

void queue_push(queue_t *queue, int elem)
{
    if (queue->is_empty)
        queue_clear(queue);

    vec_pushback(&queue->_items, &elem);
    queue->is_empty = 0;
}

int queue_pop(queue_t *queue)
{
    queue->is_empty = queue->_start + 1 >= queue->_items->size;

    if (queue->_start >= queue->_items->size)
        return -1;

    return queue->_items->data[queue->_start++];
}
