/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** the command line parser
*/

#include "../include/my.h"

bool is_pipe(char c)
{
    return c == '|';
}

int is_builtin(char *cmd)
{
    if (my_strcmp(cmd, "cd") == 0 || my_strcmp(cmd, "env") == 0 ||
        my_strcmp(cmd, "setenv") == 0 || my_strcmp(cmd, "unsetenv") == 0)
        return 0;
    return 1;
}

int exec_builtin(char *command, char ***oenv, char **env, unsigned int *l_st)
{
    char *own_com[] = {"exit", "cd", "setenv", "env", "unsetenv", NULL};
    my_built_ins_t own_functions[] = {my_exit, my_cd,
    my_setenv, my_env, my_unsetenv, NULL};
    char **token_com = TOKENIZER(command, &is_space);

    for (int i = 0; own_com[i] != NULL; i++) {
        if (my_strcmp(own_com[i], token_com[0]) == 0) {
            own_functions[i](command, oenv, l_st);
            free_2d_tab(token_com);
            return 0;
        }
    }
    if (my_strcmp(command, "echo $?") == 0){
        my_disp_status(command, l_st);
        free_2d_tab(token_com);
        return 0;
    }
    return 0;
}

int contains_redirection(char *command)
{
    if (command == NULL)
        return -1;
    for (int i = 0; command[i]; i++) {
        if (command[i] == '>' || command[i] == '<')
            return 0;
    }
    return 1;
}

void parse_cli_arg(char *command, char ***oenv, char **env, unsigned int *l_st)
{
    char **tokened = NULL;
    ind_t c = {.i = count_char_occurences(command, '|'), .j = 0, .k = 0};
    char *fs = NULL;

    if (command == NULL || command[0] == '\0')
        return;
    if (c.i >= 1) {
        handle_pipe(command, oenv, env, l_st);
        return;
    }
    if (contains_redirection(command) == 0) {
        handle_redirection(command, oenv, env, l_st);
        return;
    }
    command_manager(command, oenv, env, l_st);
}
