/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_str_to_word_array
*/

#include "../include/my.h"
bool is_semicolon(char c)
{
    return c == ';';
}

bool is_space(char c)
{
    return c == ' ' || c == '\t';
}

bool is_colon(char c)
{
    return c == ':';
}

bool is_equal(char c)
{
    return c == '=';
}

bool is_slash_or_a(char c)
{
    return c == '/' || c == '@';
}
