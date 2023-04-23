/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** catch signals
*/

#include <signal.h>

void catch_signals(void)
{
    signal(SIGINT, SIG_IGN);
}
