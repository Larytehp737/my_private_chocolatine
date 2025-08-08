/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** the main file
*/

#include "../include/my.h"

int main(int ac, char *av[], char *env[])
{
    ch_t sh = {.line = DUP(env), .str = ""};
    size_t n = 0;
    ind_t nk = {.i = 0, .j = 0};

    if (ac != 1)
        return 84;
    my_setenv("setenv OLDPWD ", &(sh.line), &nk.j);
    while (my_strcmp("exit", strtok(sh.str, "() \n\t")) != 0 && nk.i >= 0) {
        display_prompt(sh.line, nk.j);
        nk.i = getline(&(sh.str), &n, stdin);
        if (is_empty(sh.str) == 0 || nk.i == -1) {
            continue;
        }
        (sh.str)[my_strlen(sh.str) - 1] = '\0';
        cli_parser(sh.str, &(sh.line), env, &(nk.j));
    }
    free_ch(&sh);
    free_2d_tab(sh.line);
    return nk.j;
}
