/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** functions to check for binary directories
*/

#include "../include/my.h"
char *is_in_path(char *command, char *env[])
{
    char *entire_command = NULL;
    char *pv = my_getenv(env, "PATH");
    char **path_directories = (pv == NULL || my_strcmp(pv, "") == 0)
    ? NULL : TOKENIZER(pv, &is_colon);

    if (pv == NULL || my_strcmp(pv, "") == 0)
        return NULL;
    for (int i = 0; path_directories[i]; i++) {
        entire_command = my_cstrcat(path_directories[i], command, '/');
        if (access(entire_command, X_OK) == 0) {
            free_2d_tab(path_directories);
            free(pv);
            return entire_command;
        }
        free(entire_command);
    }
    free_2d_tab(path_directories);
    free(pv);
    return NULL;
}

int is_dir(char *file)
{
    struct stat buf;

    if (stat(file, &buf) == -1)
        return 1;
    if (S_ISDIR(buf.st_mode) != 0) {
        return 0;
    }
    return 1;
}

int is_binary_dir(char *dir_name, int *l_st)
{
    if (access(dir_name, X_OK) == 0 && is_dir(dir_name) == 0) {
        *l_st = 1;
        write(2, dir_name, my_strlen(dir_name));
        write(2, ": Permission denied.\n", 21);
        return 0;
    }
    return 1;
}

int is_unnormal_bin(char *file, unsigned int *l_st)
{
    int fd = open(file, O_RDONLY);
    char *signature = malloc(5);

    if (access(file, X_OK) != 0 || fd == -1)
        return 1;
    read(fd, signature, 4);
    signature[5] = '\0';
    if (my_strncmp(signature + 1, "ELF", 3) != 0) {
        write(2, file, my_strlen(file));
        write(2, ": Exec format error. Binary file not executable.\n", 49);
        free(signature);
        close(fd);
        *l_st = 1;
        return 0;
    }
    free(signature);
    close(fd);
    return 1;
}
