/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** built-in env
*/

#include "../include/my.h"
void my_env(char *command, char ***oenv, unsigned int *l_st)
{
    char **args = TOKENIZER(command, &is_space);

    if (tab_row(args) != 1) {
        *l_st = 1;
        free_2d_tab(args);
        return;
    }
    for (int i = 0; (*oenv)[i] != NULL; i++) {
        my_putstr((*oenv)[i]);
        my_putchar('\n');
    }
    *l_st = 0;
    free_2d_tab(args);
    return;
}
