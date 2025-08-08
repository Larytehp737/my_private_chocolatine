/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redir handler
*/

#include "../include/my.h"
#include <unistd.h>

void get_redir_info2(char *command, redir_t *redirs)
{
    int redir_pos;

    redir_pos = my_strstr(command, "<");
    if (redir_pos != -1) {
        redirs->input_file = strtok(command + redir_pos + 1, " \t\n");
        command[redir_pos] = '\0';
        redirs->redir_type = 2;
        return;
    }
    redir_pos = my_strstr(command, "<<");
    if (redir_pos != -1) {
        redirs->input_file = strtok(command + redir_pos + 2, " \t\n");
        command[redir_pos] = '\0';
        redirs->redir_type = 3;
        return;
    }
    return;
}

void get_redir_info(char *command, redir_t *redirs)
{
    int redir_pos;

    redir_pos = my_strstr(command, ">>");
    if (redir_pos != -1) {
        redirs->append_mode = 1;
        redirs->output_file = strtok(command + redir_pos + 2, " \t\n");
        command[redir_pos] = '\0';
        redirs->redir_type = 0;
        return;
    }
    redir_pos = my_strstr(command, ">");
    if (redir_pos != -1) {
        redirs->append_mode = 0;
        redirs->output_file = strtok(command + redir_pos + 1, " \t\n");
        command[redir_pos] = '\0';
        redirs->redir_type = 1;
        return;
    }
    get_redir_info2(command, redirs);
}

void simple_in(char *command, char ***oenv, char **env, redir_t *redirs)
{
    pid_t pid;
    unsigned int l_st = 0;

    redirs->file = open(redirs->input_file, O_RDONLY);
    if (redirs->file == -1) {
        exit(1);
    }
    pid = fork();
    if (pid == 0) {
        dup2(redirs->file, STDIN_FILENO);
        close(redirs->file);
        exec_command(command, oenv, env, &l_st);
        exit(0);
    }
    wait(NULL);
}

void outs(char *command, char ***oenv, char **env, redir_t *redirs)
{
    pid_t pid;
    unsigned int l_st = 0;

    redirs->file = open(redirs->output_file,
        ((redirs->append_mode) ? O_APPEND : O_TRUNC) |
        O_CREAT | O_WRONLY, 0644);
    if (redirs->file == -1) {
        return;
    }
    pid = fork();
    if (pid == 0) {
        dup2(redirs->file, STDOUT_FILENO);
        exec_command(command, oenv, env, &l_st);
        exit(0);
    }
    close(redirs->file);
    wait(NULL);
}

void handle_redirection(char *command, char ***oenv, char **env,
    unsigned int *l_st)
{
    redir_t redirs = {0, 0, 0, 0, 0};
    pid_t pid;

    get_redir_info(command, &redirs);
    if (redirs.redir_type == 2) {
        simple_in(command, oenv, env, &redirs);
        return;
    }
    if (redirs.redir_type == 1 || redirs.redir_type == 0) {
        outs(command, oenv, env, &redirs);
        return;
    }
    if (redirs.redir_type == 3) {
        return;
    }
}
