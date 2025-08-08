/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** the functions for exection of shells commands
*/

#include "../include/my.h"

const cli_car_t tools[] = {
    {"|", 1, "Invalid null command.\n", 0, {PIPE, NULL}},
    {";", 1, "Parse error.\n", 1, {MULTIPLE, NULL}},
    {"<", 2, "Missing name for redirect.\n", 0,
        {IN_SIMPLE_RED, IN_DOUBLE_RED, NULL}},
    {">", 2, "Missing name for redirect.\n", 0,
        {OUT_SIMPLE_RED, OUT_DOUBLE_RED, NULL}},
    {0, 0, 0, 0, 0},
};
