/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** open_file
*/

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

char *open_file(char const *file_name)
{
    char *buffer = NULL;
    int size = 0;
    struct stat stats;
    int fd = open(file_name, O_RDONLY);

    if (fd == -1)
        return NULL;
    if (stat(file_name, &stats) < 0)
        return NULL;
    size = stats.st_size;
    buffer = malloc((sizeof(char)) * (size + 1));

    if (buffer == NULL)
        return NULL;
    if (read(fd, buffer, size) < 1)
        return NULL;
    buffer[size] = '\0';
    close(fd);
    return buffer;
}
