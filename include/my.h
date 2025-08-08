/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** the header file
*/

#ifndef MY
    #define MY

// necessary libs
    #include <linux/limits.h>
    #include <unistd.h>
    #include <string.h>
    #include <signal.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/syscall.h>
    #include <stdlib.h>
    #include <dirent.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <errno.h>

// macros
    #define BLUE "\e[1;34m"
    #define GREEN "\e[1;32m"
    #define RED "\e[1;31m"
    #define COLOR_END "\e[m"
    #define TOKENIZER my_str_to_word_array
    #define SM get_session_manager
    #define DUP duplicate_tab

// structures
typedef struct indices {
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int t;
} ind_t;

    #define PIPE "|"
    #define MULTIPLE ";"
    #define OUT_SIMPLE_RED ">"
    #define OUT_DOUBLE_RED ">>"
    #define IN_SIMPLE_RED "<"
    #define IN_DOUBLE_RED "<<"

typedef char *cli_operator_t;
//typedef char *cli_operator_func_t;

typedef struct cli_tools_caracteristics {
    char *tool;
    int max_occur;
    char *err_message;
    int can_end_line;
    char *posible_comb[20];
    // cli_operator_func_t function[];
} cli_car_t;

extern const cli_car_t tools[];

typedef struct charices {
    char **line;
    char *info;
    char *str;
    char *envi;
    char *sm;
} ch_t;

typedef enum cli_operators {
    INSTRUCTION,
    OPERATOR
} cli_op_t;

// op for operator
typedef struct syntax_tree_for_cli_parsing {
    cli_op_t type;
    char *value;
    struct syntax_tree_for_cli_parsing *left;
    struct syntax_tree_for_cli_parsing *right;
} my_ast_t;

typedef struct for_redir {
    char *input_file;
    char *output_file;
    int append_mode;
    int redir_type;
    int file;
} redir_t;

typedef void(*my_built_ins_t)(char *, char ***, unsigned int *);

// mem manipulation functions
char **alloc_2d_char(int row, int *col);
void free_2d_tab(char **tab);
int tab_row(char **tab);
char **duplicate_tab(char **src);
void remove_from_2d_array(char ***tab, char *str);
void update_in_2d_array(char ***tab, char *str);
void add_to_2d_array(char ***tab, char *str);
void free_ch(ch_t *it);

// functions for tokenizing strings
bool is_space(char c);
bool is_semicolon(char c);
bool is_colon(char c);
bool is_equal(char c);
bool is_slash_or_a(char c);
int get_row(char *str, bool(*is_delim)(char c));
void col_funct(ind_t *c, char *str, bool(*is_delim)(char c), int *col);
int *get_col(char *str, bool(*is_delim)(char c), int row);
char **my_str_to_word_array(char *str, bool(*is_delim)(char));

// built-ins functions
void my_exit(char *command, char ***env, unsigned int *l_st);
void my_cd(char *command, char ***env, unsigned int *l_st);
void my_setenv(char *command, char ***env, unsigned int *l_st);
void my_env(char *command, char ***env, unsigned int *l_st);
void my_unsetenv(char *command, char ***env, unsigned int *l_st);
void my_disp_status(char *command, unsigned int *l_st);

// utils functions
void my_putchar(char c);
void my_putstr(char *str);
void my_putnbr(int nb);
int my_strlen(char *str);
char *my_strdup(char *str);
int my_strcmp(char *str1, char *str2);
int my_strncmp(char *str1, char *str2, int n);
int my_getnbr(char *str);
char *my_cstrcat(char *start, char *end, char c);
void ternary_own(bool condition, void(*cor)(void *),
    void(*inc)(void *), char *var);
void ignore(void *var);
int is_dir(char *file);
int is_binary_dir(char *dir_name, int *l_st);
int is_unnormal_bin(char *file, unsigned int *l_st);
char *is_in_path(char *command, char *env[]);
int is_alphanum(char c);
int count_char_occurences(char *str, char c);

// for prompt
void display_prompt(char **env, int st);
char *my_getenv(char **env, char *name);
char *get_session_manager(char *env[]);
void status_disp(int st);

// new
int is_builtin(char *cmd);
int exec_builtin(char *command, char ***oenv, char **env, unsigned int *l_st);
int contains_redirection(char *command);
void parse_cli_arg(char *command, char ***oenv,
    char **env, unsigned int *l_st);
void get_redir_info2(char *command, redir_t *redirs);
void get_redir_info(char *command, redir_t *redirs);
void simple_in(char *command, char ***oenv, char **env, redir_t *redirs);
void outs(char *command, char ***oenv, char **env, redir_t *redirs);
void handle_redirection(char *command, char ***oenv, char **env,
    unsigned int *l_st);
int **prepare_pipes(int n);
void close_pipes_and_free(int **fds, int n);
void redirect_fds(int **fds, int i, int n);
void exec_command(char *cmd, char ***oenv, char **env, unsigned int *l_st);
void handle_pipe(char *command, char ***oenv, char **env, unsigned int *l_st);
bool is_pipe(char c);
int my_strstr(char *str1, char *str2);
int count_char_occurences(char *str, char c);
int get_last_appear(char *str, char c);
int get_consecutive_occurence(char *str, char c);
int op_end_line(char *command, char c);
void status_disp(int st);
int is_empty(char *command);

// main functions
void parse_cli_arg(char *command, char ***oenv,
    char **env, unsigned int *l_st);
void shell_native_functions(char **args, char ***env, unsigned int *l_st);
void command_manager(char *command, char ***oenv,
    char **env, unsigned int *l_st);
void cli_parser(char *command, char ***oenv,
    char **env, unsigned int *l_st);
//int main(int ac, char *av[], char *env[]);

#endif
