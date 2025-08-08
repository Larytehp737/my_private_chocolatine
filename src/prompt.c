/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** the functions that intervenes in the prompt display
*/

#include "../include/my.h"

char *my_getenv(char **env, char *name)
{
    ch_t d;
    ind_t c = {.i = 0, .j = 0};

    for (; c.i == 0 && (env[c.j]) != NULL; c.j++) {
        d.line = TOKENIZER(env[c.j], &is_equal);
        if (my_strcmp((d.line)[0], name) == 0) {
            c.i = 1;
            free_2d_tab(d.line);
            break;
        }
        free_2d_tab(d.line);
    }
    if (c.i == 0)
        return NULL;
    d.line = TOKENIZER(env[c.j], &is_equal);
    d.info = (((d.line)[1] == NULL) ? "" : my_strdup((d.line)[1]));
    free_2d_tab(d.line);
    return d.info;
}

char *get_session_manager(char *env[])
{
    char **line;
    ind_t c = {.i = 0, .j = 0};
    char *it;

    while (c.i == 0 && env[c.j] != NULL) {
        line = TOKENIZER(env[c.j], &is_equal);
        if (my_strcmp(line[0], "SESSION_MANAGER") == 0) {
            c.i = 1;
            break;
        }
        c.j++;
        free_2d_tab(line);
    }
    free_2d_tab(line);
    if (c.i == 0)
        return NULL;
    line = TOKENIZER(env[c.j], &is_slash_or_a);
    it = my_strdup(line[1]);
    free_2d_tab(line);
    return it;
}

void display_prompt(char **oenv, int st)
{
    ch_t d = {.info = my_getenv(oenv, "PWD"), .envi = my_getenv(oenv, "USER"),
    .sm = my_getenv(oenv, "HOST")};

    status_disp(st);
    if (d.info == NULL || d.envi == NULL || d.sm == NULL) {
        free_ch(&d);
        my_putstr("$> ");
        return;
    }
    my_putstr(GREEN);
    my_putstr(d.envi);
    my_putchar('@');
    my_putstr(d.sm);
    my_putstr(COLOR_END);
    my_putstr(BLUE);
    my_putstr(d.info);
    my_putstr(COLOR_END);
    my_putstr("$ ");
    free_ch(&d);
}
