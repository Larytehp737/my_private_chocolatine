/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** let command line be safe
*/

#include "../include/my.h"

int my_strstr(char *str1, char *str2)
{
    int j = 0;
    int t = 0;

    if (!str1 || !str2)
        return -1;
    for (int i = 0; str1[i] != 0; i++) {
        if (my_strncmp(str1 + i, str2, my_strlen(str2)) == 0)
            return i;
    }
    return -1;
}

int count_char_occurences(char *str, char c)
{
    int j = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            j++;
    }
    return j;
}

int get_last_appear(char *str, char c)
{
    int oc = -1;

    if (str == NULL)
        return oc;
    for (int j = 0; str[j]; j++) {
        if (str[j] == c)
            oc = j;
    }
    return oc;
}

int get_consecutive_occurence(char *str, char c)
{
    int act = 0;
    int max_act = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        act = 0;
        while (str[i] == c && str[i] != '\0') {
            act++;
            i++;
        }
        max_act = (act > max_act) ? act : max_act;
    }
    return max_act;
}

int op_end_line(char *command, char c)
{
    int i = 0;
    int found = 0;

    if (!command)
        return 0;
    while (command[i]) {
        if (command[i] == c)
            found = 1;
        if (command[i] != c && found && !is_space(command[i]))
            found = 0;
        i++;
    }
    return found;
}
