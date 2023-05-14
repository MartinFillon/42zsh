/*
** EPITECH PROJECT, 2022
** my_lib
** File description:
** stupid utils
*/

#ifndef INCLUDE_MY_UTILS_
    #define INCLUDE_MY_UTILS_
    #include <stddef.h>

    #define MIN(x, y) ((x) < (y) ? (x) : (y))
    #define MAX(x, y) ((x) > (y) ? (x) : (y))

    #define FABS(x) ((x) < 0.0 ? -(x) : (x))
    #define ABS(x)  ((x) < 0 ? -(x) : (x))

    #define UNUSED __attribute__((unused))


void my_swap(void *a, void *b, size_t size);
void my_vfree(int ac, ...);


#endif /* INCLUDE_MY_UTILS_ */
