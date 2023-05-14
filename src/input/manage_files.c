/*
** EPITECH PROJECT, 2023
** 42zsh
** File description:
** manage_files
*/

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include "my_str.h"
#include "my_map.h"

#include "mysh/mysh.h"
#include "mysh/history.h"

static char *open_file(char const *file_name)
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

void save_history(history_t *history, char const *filename)
{
    FILE *fp = fopen(filename, "w+");

    if (fp == NULL)
        return;

    for (size_t i = 0; i < history->entries->size; i++) {
        fprintf(fp, "#+%ld\n", history->entries->data[i].timestamp);
        fprintf(fp, "%s\n", history->entries->data[i].command->data);
    }
    fclose(fp);
}

static void parse_history_file(
    history_t *history, history_entry_t entry, vec_str_t *lines, size_t i
)
{
    str_t *tmp = NULL;

    if (str_startswith(lines->data[i], STR("#+")) == 1){
        tmp = str_create(lines->data[i]->data);
        str_slice(&tmp, 2, lines->data[i]->length);
        if (atof(tmp->data) == 0 && tmp->data[0] != '0')
            return;
        entry.timestamp = atof(tmp->data);
        entry.command = lines->data[i + 1];
        vec_pushback(&history->entries, &entry);
        free(tmp);
    }
}

void load_diff_history(history_t *history, char const *filename)
{
    history_entry_t entry;
    char *buffer = open_file(filename);
    str_t *file_content = NULL;
    vec_str_t *lines = NULL;

    if (buffer == NULL){
        free(buffer);
        return;
    }
    file_content = str_create(buffer);
    free(buffer);
    lines = str_split(file_content, STR("\n"));
    if (lines == NULL){
        free(file_content);
        free(lines);
        return;
    }
    for (size_t i = 0;i < lines->size;i++)
        parse_history_file(history, entry, lines, i);
    free(file_content);
}
