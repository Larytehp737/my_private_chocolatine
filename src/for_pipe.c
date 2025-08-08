/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** pipe handler
*/

#include "../include/my.h"

int **prepare_pipes(int n)
{
    int **fds = malloc(sizeof(int *) * (n - 1));

    if (!fds)
        return NULL;
    for (int i = 0; i < n - 1; i++) {
        fds[i] = malloc(sizeof(int) * 2);
        if (!fds[i] || pipe(fds[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }
    return fds;
}

void close_pipes_and_free(int **fds, int n)
{
    for (int i = 0; i < n - 1; i++) {
        close(fds[i][0]);
        close(fds[i][1]);
        free(fds[i]);
    }
    free(fds);
}

void redirect_fds(int **fds, int i, int n)
{
    if (i > 0)
        dup2(fds[i - 1][0], STDIN_FILENO);
    if (i < n - 1)
        dup2(fds[i][1], STDOUT_FILENO);
    for (int j = 0; j < n - 1; j++) {
        close(fds[j][0]);
        close(fds[j][1]);
    }
}

void exec_command(char *cmd, char ***oenv, char **env, unsigned int *l_st)
{
    char **argv = TOKENIZER(cmd, &is_space);

    if (is_builtin(argv[0]) == 0)
        exec_builtin(cmd, oenv, env, l_st);
    else
        shell_native_functions(argv, &env, l_st);
}

void handle_pipe(char *command, char ***oenv, char **env, unsigned int *l_st)
{
    char **cmds = TOKENIZER(command, &is_pipe);
    int n = tab_row(cmds);
    int **fds = prepare_pipes(n);
    pid_t pid;

    for (int i = 0; i < n; i++) {
        if (contains_redirection(cmds[i]) == 0)
            continue;
        pid = fork();
        if (pid == 0) {
            redirect_fds(fds, i, n);
            exec_command(cmds[i], oenv, env, l_st);
            exit(0);
        }
    }
    close_pipes_and_free(fds, n);
    for (int i = 0; i < n; i++)
        wait(NULL);
    free_2d_tab(cmds);
}
