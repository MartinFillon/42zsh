/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** error management
*/

#include <stdio.h>
#include <sys/wait.h>

static const char *ERROR[] = {
    "",
    "Hangup",
    "Interrupt",
    "Quit",
    "Illegal instruction",
    "Trace/BPT trap",
    "Abort",
    "EMT trap",
    "Floating exception",
    "Killed",
    "Bus error",
    "Segmentation fault",
    "Bad system call",
    "Broken pipe",
    "Alarm clock",
    "Terminated",
    "urgent condition on IO channel",
};

static const int ERROR_ST = sizeof(ERROR) / sizeof(char *);

void exec_error(int code)
{
    int has_error;
    if ((has_error = WTERMSIG(code) > 0 && WTERMSIG(code) <= ERROR_ST)) {
        dprintf(2, "%s", ERROR[WTERMSIG(code)]);
    }
    if ((has_error = WCOREDUMP(code))) {
        dprintf(2, " (core dumped)");
    }
    if (has_error) {
        dprintf(2, "\n");
    }
}
