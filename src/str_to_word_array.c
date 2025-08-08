/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_str_to_word_array
*/

#include "../include/my.h"

int get_row(char *str, bool(*is_delim)(char c))
{
    ind_t c = {.i = 0};
    int row = 0;

    while (str[c.i] != '\0') {
        if (c.i == 0 && !is_delim(str[c.i])) {
            row++;
            c.i++;
            continue;
        }
        if (c.i == 0 && is_delim(str[c.i])) {
            c.i++;
            continue;
        }
        if (!is_delim(str[c.i]) && (is_delim(str[c.i - 1])
        || str[c.i - 1] == '\0')) {
            row++;
        }
        c.i++;
    }
    return row;
}

void col_funct(ind_t *c, char *str, bool(*is_delim)(char c), int *col)
{
    while (is_delim(str[c->i])) {
        c->i++;
        c->k++;
    }
    if (c->k != 0) {
        c->k = 0;
        if (col[c->j] != 0)
            c->j++;
    }
}

int *get_col(char *str, bool(*is_delim)(char c), int row)
{
    int *col = malloc(sizeof(int) * row);
    ind_t c = {.i = 0, .j = 0, .k = 0};

    if (col == NULL)
        return NULL;
    for (c.i = 0; c.i < row; c.i++)
        col[c.i] = 0;
    c.i = 0;
    while (str[c.i] != '\0') {
        col_funct(&c, str, is_delim, col);
        if (str[c.i] == '\0')
            break;
        if (!is_delim(str[c.i])) {
            col[c.j]++;
            c.i++;
        }
    }
    return col;
}

static void escape_delim(bool(*is_delim)(char c), ind_t *c, char *str)
{
    for (; is_delim(str[c->k]); c->k++);
}

char **my_str_to_word_array(char *str, bool(*is_delim)(char c))
{
    char **dest = NULL;
    int row = get_row(str, is_delim);
    int *col = get_col(str, is_delim, row);
    ind_t c = {.i = 0, .j = 0, .k = 0, .l = 0};

    dest = alloc_2d_char(row, col);
    if (dest == NULL)
        return NULL;
    for (c.i = 0; c.i < row; c.i++) {
        for (c.j = 0; c.j < col[c.i]; c.j++) {
            escape_delim(is_delim, &c, str);
            dest[c.i][c.j] = str[c.k];
            c.k++;
        }
        dest[c.i][c.j] = '\0';
    }
    dest[c.i] = NULL;
    free(col);
    return dest;
}
