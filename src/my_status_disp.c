/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** built-in echo $?
*/

#include "../include/my.h"

void my_disp_status(char *command, unsigned int *l_st)
{
    my_putnbr(*l_st);
    *l_st = 0;
    my_putchar('\n');
    return;
}
