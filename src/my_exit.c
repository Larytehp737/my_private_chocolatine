/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** built_in exit
*/

#include "../include/my.h"

void my_exit(char *command, char ***env, unsigned int *l_st)
{
    char **args = TOKENIZER(command, &is_space);

    if (tab_row(args) > 2) {
        *l_st = 1;
        write(2, "exit: Expression Syntax.\n", 25);
        free_2d_tab(args);
        return;
    } else {
        write(1, "exit\n", 5);
        if (!args[1]) {
            *l_st = 0;
            free_2d_tab(args);
            return;
        }
        *l_st = my_getnbr(args[1]);
        free_2d_tab(args);
        return;
    }
}
