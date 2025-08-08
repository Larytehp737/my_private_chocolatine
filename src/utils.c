/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** utils functions for display
*/

#include "../include/my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        my_putnbr(-nb);
    }
    if (nb <= 9 && nb >= 0) {
        my_putchar(nb + 48);
    } else {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    }
}

int my_strlen(char *str)
{
    int len = 0;

    while (*str) {
        len++;
        *str++;
    }
    return len;
}

char *my_strdup(char *str)
{
    char *dest = malloc(sizeof(char) * (my_strlen(str) + 1));
    int i = 0;

    if (dest == NULL)
        return NULL;
    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
    dest[my_strlen(str)] = '\0';
    return dest;
}
