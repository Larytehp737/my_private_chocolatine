/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** the functions for exection of shells commands
*/

#include "../include/my.h"
//l_st for latest status

void handle_signal(int *l_st)
{
    if (WTERMSIG(*l_st) == SIGSEGV) {
        write(2, "Segmentation fault (core dumped)\n", 33);
    } else if (WTERMSIG(*l_st) == SIGFPE) {
        write(2, "Floating exception (core dumped)\n", 33);
    }
}

int execute_cli_basic(char *command, char **oenv, char **args, int *l_st)
{
    pid_t child;
    int status = 0;
    int exec = 0;

    child = fork();
    if (child > 0) {
        wait(&status);
    } else if (child == 0) {
        exec = execve(command, args, oenv);
    } else {
        *l_st = 1;
        return *l_st;
    }
    *l_st = WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        *l_st = status;
        handle_signal(l_st);
    }
    return *l_st;
}

// ec for entire_command
void shell_native_functions(char **args, char ***env, unsigned int *l_st)
{
    char *ec = NULL;

    if (args == NULL) {
        *l_st = 1;
        return;
    }
    if (is_binary_dir(args[0], l_st) == 0
    || is_unnormal_bin(args[0], l_st) == 0)
        return;
    ec = is_in_path(args[0], *env);
    if ((access(args[0], X_OK) == 0 || ec != NULL) && is_dir(args[0]) == 1) {
        execute_cli_basic((ec == NULL) ? args[0] : ec, *env, args, l_st);
    } else {
        write(2, args[0], my_strlen(args[0]));
        write(2, ": Command not found.\n", 21);
        *l_st = 1;
    }
    free(ec);
    free_2d_tab(args);
}

void command_manager(char *command, char ***oenv,
    char **env, unsigned int *l_st)
{
    char *own_com[] = {"exit", "cd", "setenv", "env", "unsetenv", NULL};
    my_built_ins_t own_functions[] = {my_exit, my_cd,
    my_setenv, my_env, my_unsetenv, NULL};
    char **token_com = TOKENIZER(command, &is_space);

    for (int i = 0; own_com[i] != NULL; i++) {
        if (my_strcmp(own_com[i], token_com[0]) == 0) {
            own_functions[i](command, oenv, l_st);
            free_2d_tab(token_com);
            return;
        }
    }
    if (my_strcmp(command, "echo $?") == 0){
        my_disp_status(command, l_st);
        free_2d_tab(token_com);
        return;
    }
    shell_native_functions(token_com, &env, l_st);
    return;
}

static int cli_is_fine(char *command, unsigned int *l_st)
{
    for (int i = 0; tools[i].err_message != 0; i++) {
        if (get_consecutive_occurence(command, tools[i].tool[0])
            > tools[i].max_occur) {
            write(2, tools[i].err_message, my_strlen(tools[i].err_message));
            *l_st = 1;
            return 1;
        }
    }
    return 0;
}

static int cmd_is_fine(char *command, unsigned int *l_st)
{
    for (int i = 0; tools[i].err_message != 0; i++) {
        if (tools[i].can_end_line == 0 &&
        op_end_line(command, tools[i].tool[0]) == 1 &&
        count_char_occurences(command, tools[i].tool[0]) > 0) {
            write(2, tools[i].err_message, my_strlen(tools[i].err_message));
            *l_st = 1;
            return 1;
        }
    }
    *l_st = 0;
    return 0;
}

static int empty_line(char *str)
{
    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return 1;
    return 0;
}

void cli_parser(char *command, char ***oenv,
    char **env, unsigned int *l_st)
{
    char **commands = NULL;

    if (cli_is_fine(command, l_st) != 0 || empty_line(command) == 0) {
        return;
    }
    commands = TOKENIZER(command, &is_semicolon);
    for (int i = 0; commands[i]; i++) {
        cmd_is_fine(commands[i], l_st);
        if (*l_st != 0)
            break;
        parse_cli_arg(commands[i], oenv, env, l_st);
    }
    free_2d_tab(commands);
}
