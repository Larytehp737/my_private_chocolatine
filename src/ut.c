/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** the utils globally
*/

#include "../include/my.h"

void status_disp(int st)
{
    my_putstr("[");
    my_putstr(RED);
    my_putnbr(st);
    my_putstr(COLOR_END);
    my_putstr("]-");
}

int is_empty(char *command)
{
    for (int i = 0; command[i]; i++)
        if (command[i] != ' ' && command[i] != '\n')
            return 1;
    return 0;
}
