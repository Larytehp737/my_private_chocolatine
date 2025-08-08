/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** built-in cd
*/

#include "../include/my.h"

void cd_errors(void)
{
    char *error = strerror(errno);

    write(2, ": ", 2);
    write(2, error, my_strlen(error));
    write(2, ".\n", 2);
}

void go_to_new_dir(char ***env, char *dest, unsigned int *l_st)
{
    char oldd[1024];
    char *old = NULL;
    char *entire = NULL;

    if (dest == NULL)
        return;
    old = getcwd(oldd, 1024);
    old = my_cstrcat("setenv OLDPWD", old, ' ');
    *l_st = (chdir(dest) == 0) ? 0 : 1;
    if (*l_st != 0) {
        entire = my_cstrcat(oldd, dest, '/');
        write(2, dest, my_strlen(dest));
        cd_errors();
    } else {
        my_setenv(old, env, l_st);
        old = getcwd(oldd, 1024);
        old = my_cstrcat("setenv PWD", old, ' ');
        my_setenv(old, env, l_st);
    }
}

void my_cd(char *command, char ***env, unsigned int *l_st)
{
    char **args = TOKENIZER(command, &is_space);
    int ac = tab_row(args);
    char *where = NULL;

    if (ac > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        *l_st = 1;
        return;
    }
    if (ac == 1 || (ac == 2 && my_strcmp(args[1], "~") == 0)) {
        where = my_getenv(*env, "HOME");
    } else if (ac == 2 && my_strcmp(args[1], "-") == 0) {
        where = my_getenv(*env, "OLDPWD");
    } else {
        where = my_strdup(args[1]);
    }
    go_to_new_dir(env, where, l_st);
    ternary_own(where != NULL && where[0] == '\0', &ignore, &free, where);
    free_2d_tab(args);
    return;
}
