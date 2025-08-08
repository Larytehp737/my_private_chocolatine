/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** unsetenv
*/

#include "../include/my.h"

void ignore(void *var)
{
    return;
}

void ternary_own(bool condition, void(*cor)(void *),
    void(*inc)(void *), char *var)
{
    if (condition)
        cor(var);
    else
        inc(var);
}

void my_unsetenv(char *command, char ***oenv, unsigned int *l_st)
{
    char **args = NULL;
    int ac = get_row(command, &is_space);
    char *var = NULL;

    if (ac == 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        *l_st = 1;
        return;
    }
    args = TOKENIZER(command, &is_space);
    if (args == NULL)
        return;
    for (int i = 1; i < ac; i++) {
        var = my_getenv(*oenv, args[i]);
        if (var != NULL)
            remove_from_2d_array(oenv, args[i]);
    }
    ternary_own(var != NULL && var[0] == '\0', &ignore, &free, var);
    free_2d_tab(args);
    *l_st = 0;
}
