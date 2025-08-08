/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** built-in setenv
*/

#include "../include/my.h"
const char *empty = "";

void pseudo_errors(int ac, char ***env, unsigned int *l_st)
{
    if (ac == 1) {
        my_env("env", env, l_st);
        return;
    } else if (ac > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        *l_st = 1;
        return;
    }
}

void add_or_update(char *var, char ***env, char *varval)
{
    char *val = my_getenv(*env, var);

    if (val == NULL)
        add_to_2d_array(env, varval);
    else
        update_in_2d_array(env, varval);
}

int check_variable_name_integrity(char *var_name, unsigned int *l_st)
{
    if ((var_name[0] < 'a' || var_name[0] > 'z') &&
    (var_name[0] < 'A' || var_name[0] > 'Z') && var_name[0] != '_') {
        *l_st = 1;
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return 1;
    }
    for (int i = 1; var_name[i]; i++) {
        if (is_alphanum(var_name[i]) != 0) {
            *l_st = 1;
            write(2, "setenv: Variable name must contain alphanumeric"
            " characters.\n", 60);
            return 1;
        }
    }
    return 0;
}

void my_setenv(char *command, char ***env, unsigned int *l_st)
{
    char **args = NULL;
    int ac = get_row(command, &is_space);
    char *built_var = NULL;

    if (ac != 2 && ac != 3) {
        pseudo_errors(ac, env, l_st);
        return;
    }
    args = TOKENIZER(command, &is_space);
    if (check_variable_name_integrity(args[1], l_st) == 1) {
        free_2d_tab(args);
        return;
    }
    built_var = my_cstrcat(args[1],
    (args[2] == NULL) ? ("") : (args[2]), '=');
    add_or_update(args[1], env, built_var);
    *l_st = 0;
    free(built_var);
    free_2d_tab(args);
}
