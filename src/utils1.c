/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** utils for strings manip
*/

#include "../include/my.h"

int my_strcmp(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return -1;
    while (*str1 == *str2 && *str1) {
        ++str1;
        ++str2;
    }
    return (*str1 - *str2);
}

int my_strncmp(char *str1, char *str2, int n)
{
    int i = 0;

    if (str1 == NULL || str2 == NULL)
        return -1;
    while (str1[i] == str2[i] && str1[i] && i < n - 1) {
        i++;
    }
    return (str1[i] - str2[i]);
}

int my_getnbr(char *str)
{
    int i = 0;
    int sign = 1;
    int answer = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') {
            sign *= -1;
        }
        i++;
    }
    while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57) {
        answer = (answer * 10) + (str[i] - 48);
        i++;
    }
    return answer * sign;
}

char *my_cstrcat(char *start, char *end, char k)
{
    char *dest = malloc(sizeof(char) + (my_strlen(start)
    + my_strlen(end) + 2));
    ind_t c = {.i = 0, .j = 0};

    if (dest == NULL)
        return NULL;
    for (c.i = 0; start[c.i] != '\0'; c.i++) {
        dest[c.i] = start[c.i];
    }
    dest[c.i] = k;
    c.i++;
    for (c.j = 0; end[c.j] != '\0'; c.j++) {
        dest[c.i] = end[c.j];
        c.i++;
    }
    dest[c.i] = '\0';
    return dest;
}

int is_alphanum(char c)
{
    if (c >= '0' && c <= '9')
        return 0;
    if (c == '_')
        return 0;
    if (c >= 'a' && c <= 'z')
        return 0;
    if (c >= 'A' && c <= 'Z')
        return 0;
    return 1;
}
