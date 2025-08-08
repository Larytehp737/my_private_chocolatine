/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** utilitary functions for mem manipulations
*/

#include "../include/my.h"

char **alloc_2d_char(int row, int *col)
{
    int i = 0;
    char **dest = NULL;

    dest = malloc(sizeof(char *) * (row + 1));
    if (dest == NULL)
        return NULL;
    for (i = 0; i < row; i++) {
        dest[i] = malloc(sizeof(char *) * (col[i] + 1));
        if (dest[i] == NULL)
            return NULL;
    }
    return dest;
}

void free_2d_tab(char **tab)
{
    for (int i = 0; tab[i]; i++) {
        free(tab[i]);
    }
    free(tab);
}

int tab_row(char **tab)
{
    int row = 0;

    for (int i = 0; tab[i]; i++) {
        row++;
    }
    return row;
}

char **duplicate_tab(char **src)
{
    int row = tab_row(src);
    char **dest = malloc(sizeof(char *) * (row + 1));
    int i = 0;

    if (dest == NULL)
        return NULL;
    for (i = 0; src[i] != NULL; i++) {
        dest[i] = my_strdup(src[i]);
    }
    dest[i] = NULL;
    return dest;
}

void free_ch(ch_t *it)
{
    free(it->envi);
    free(it->info);
    free(it->sm);
    free(it->str);
}
