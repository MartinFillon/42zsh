/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** queue
*/

#ifndef MY_QUEUE_
    #define MY_QUEUE_

    #include "my_vec.h"


typedef struct queue_s {
    int is_empty;
    size_t _start;
    vec_int_t *_items;
} queue_t;


/**
 * @brief creates a new queue
 *
 * @param initial_size the initial size of the queue
 *
 * @return the new queue
 */
queue_t *queue_create(size_t initial_size);

/**
 * @brief pushes an element in the queue
 *
 */
void queue_push(queue_t *queue, int elem);

/**
 * @brief clears the queue
 *
 */
void queue_clear(queue_t *queue);

/**
 * @brief pops an element from the queue
 *
 * @return the popped element
 */
int queue_pop(queue_t *queue);

/**
 * @brief frees a queue
 *
 */
void queue_free(queue_t *queue);


#endif /* MY_QUEUE_ */
