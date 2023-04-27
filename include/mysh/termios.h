/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** termios
*/

#ifndef TERMIOS_H_
    #define TERMIOS_H_
    #include "my_str.h"
    #define DELETE  127
    #define ENTER  '\n'
    #define ARROW   '['
    #define UP      'A'
    #define DOWN    'B'
    #define RIGHT   'C'
    #define LEFT    'D'

str_t *stock_input(void);

#endif /* !TERMIOS_H_ */
