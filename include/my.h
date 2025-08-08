/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** the header file
*/

#ifndef MY
    #define MY

// necessary libs
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

typedef struct charices {
    char **line;
    char *info;
    char *str;
    char *envi;
    char *sm;
} ch_t;

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

// for prompt
void display_prompt(char **env, int st);
char *my_getenv(char **env, char *name);
char *get_session_manager(char *env[]);
void status_disp(int st);

// main functions
void command_manager(char *command, char ***oenv,
    char **env, unsigned int *l_st);
void cli_parser(char *command, char ***oenv,
    char **env, unsigned int *l_st);
//int main(int ac, char *av[], char *env[]);

#endif
