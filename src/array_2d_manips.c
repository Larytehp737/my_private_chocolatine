/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** two dimensinal arrays manipulations
*/

#include "../include/my.h"

void remove_from_2d_array(char ***tab, char *str)
{
    char **temp = DUP(*tab);
    int size = tab_row(*tab);
    int len = my_strlen(str);
    ind_t c = {.i = 0, .j = 0};
    char **new = malloc(sizeof(char *) * (size));

    free_2d_tab(*tab);
    if (new == NULL) {
        free_2d_tab(temp);
        return;
    }
    for (c.i = 0; temp[c.i] != NULL; c.i++) {
        if (my_strncmp(temp[c.i], str, len) == 0)
            continue;
        new[c.j] = my_strdup(temp[c.i]);
        c.j++;
    }
    free_2d_tab(temp);
    new[c.j] = NULL;
    *tab = new;
}

void update_in_2d_array(char ***tab, char *str)
{
    char **temp = DUP(*tab);
    int len = tab_row(*tab);
    char *new = my_strdup(str);
    char *name = strtok(new, "=");
    char *act = NULL;

    for (int i = 0; temp[i]; i++) {
        act = my_strdup(temp[i]);
        if (my_strcmp(strtok(act, "="), name) == 0) {
            free(temp[i]);
            temp[i] = my_strdup(str);
            free(act);
            break;
        }
        free(act);
    }
    free(name);
    free_2d_tab(*tab);
    *tab = temp;
}

void add_to_2d_array(char ***tab, char *str)
{
    char **temp = DUP(*tab);
    int len = tab_row(*tab);
    char **new = malloc(sizeof(char *) * (len + 2));
    int i = 0;

    for (i = 0; temp[i]; i++) {
        new[i] = my_strdup(temp[i]);
    }
    free_2d_tab(temp);
    new[i] = my_strdup(str);
    new[len + 1] = NULL;
    free_2d_tab(*tab);
    *tab = new;
}
