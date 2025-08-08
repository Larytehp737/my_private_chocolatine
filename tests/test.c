/*
** EPITECH PROJECT, 2025
** unit_test
** File description:
** unit_test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(get_consecutive_occurence, really_get_max_occurences)
{
    cr_assert(get_consecutive_occurence("ls || kd | yt |", '|') == 2);
    cr_assert(get_consecutive_occurence("ls || kd || yt |||", '|') == 3);
    cr_assert(get_consecutive_occurence("ls < kd >> yt >>> ", '>') == 3);
    cr_assert(get_consecutive_occurence("ls ><><<> kd | yt >>>>>", '<') == 2);
    cr_assert(get_consecutive_occurence("ls ;;;;;||;;; kd |;|;|;| yt |", ';') == 5);
    cr_assert(get_consecutive_occurence(NULL, '|') == 0);
    cr_assert(get_consecutive_occurence("ls kd yt", '|') == 0);
    cr_assert(get_consecutive_occurence("ls | kd | yt", '|') == 1);
}

Test(op_end_line, check_if_end_line)
{
    cr_assert(op_end_line("ls || kd | yt |", '|') == 1);
    cr_assert(op_end_line("ls || kd || yt ||    \t", '|') == 1);
    cr_assert(op_end_line("ls < kd >> yt >>> jh", '>') == 0);
    cr_assert(op_end_line("ls ><><<> kd | yt >>>>>  gh ", '<') == 0);
    cr_assert(op_end_line("ls ;;;;;||;;; kd |;|;|;| yt |", ';') == 0);
    cr_assert(op_end_line(NULL, '|') == 0);
}

// test delim_functions
Test(is_space, space_delim)
{
    cr_assert(!is_space('c'));
    cr_assert(is_space(' '));
}

Test(is_semicolon, semicolon_delim)
{
    cr_assert(!is_semicolon('c'));
    cr_assert(is_semicolon(';'));
}

Test(is_colon, colon_delim)
{
    cr_assert(!is_colon('c'));
    cr_assert(is_colon(':'));
}

Test(is_equal, equal_delim)
{
    cr_assert(!is_equal('c'));
    cr_assert(is_equal('='));
}

Test(is_slash_or_a, slash_or_a_delim)
{
    cr_assert(!is_slash_or_a('c'));
    cr_assert(is_slash_or_a('/'));
}

Test(my_strstr, test_it1)
{
    cr_assert(my_strstr("Hello", "Hel") == 0);
    cr_assert(my_strstr(NULL, "Hel") == -1);
    cr_assert(my_strstr("Hello", "dgf") == -1);
}

Test(count_char_occurences, test_it2)
{
    cr_assert(count_char_occurences("Hello", 'l') == 2);
    cr_assert(count_char_occurences(NULL, 'l') == 0);
    cr_assert(count_char_occurences("Hello", 'd') == 0);
}

Test(get_last_appear, test_it3)
{
    cr_assert(get_last_appear("Hello", 'l') == 3);
    cr_assert(get_last_appear(NULL, 'l') == -1);
    cr_assert(get_last_appear("Hello", 'd') == -1);
}

Test(is_empty, test_it4)
{
    cr_assert(is_empty("Hello") == 1);
    cr_assert(is_empty("                 ") == 0);
}

Test(status_disp, test_it5, .init = redirect_all_std)
{
    status_disp(0);
    cr_assert_stdout_eq_str("[\e[1;31m0\e[m]-");
}

Test(my_putchar, test_it6, .init = redirect_all_std)
{
    my_putchar('c');
    cr_assert_stdout_eq_str("c");
}

Test(my_putstr, test_it7, .init = redirect_all_std)
{
    my_putstr("Please god!");
    cr_assert_stdout_eq_str("Please god!");
}

Test(my_putnbr, test_it8, .init = redirect_all_std)
{
    my_putnbr(100);
    my_putnbr(-10);
    cr_assert_stdout_eq_str("100-10");
}

Test(my_strlen, test_it9)
{
    cr_assert(my_strlen("Hello") == 5);
}

Test(my_strcmp, test_it10)
{
    cr_assert(my_strcmp("Hello", "Hello") == 0);
    cr_assert(my_strcmp("Hello", "Helo") != 0);
    cr_assert(my_strcmp(NULL, "Helo") == -1);
}

Test(my_getnbr, test_it11)
{
    cr_assert(my_getnbr("Hello") == 0);
    cr_assert(my_getnbr("12") == 12);
    cr_assert(my_getnbr("-12") == -12);
}

Test(my_strncmp, test_it12)
{
    cr_assert(my_strncmp("Hello", "Hello", 2) == 0);
    cr_assert(my_strncmp("Hello", "Hedlo", 3) != 0);
    cr_assert(my_strncmp(NULL, "Helo", 2) == -1);
}

Test(my_strdup, test_it13)
{
    char *str = my_strdup("Hello");
    char *str1 = my_strdup("Helo");
    cr_assert(my_strcmp(str, "Hello") == 0);
    cr_assert(my_strcmp(str, "Helo") != 0);
    cr_assert(my_strcmp(str1, "Helo") == 0);
}

Test(my_cstrcat, test_it14)
{
    char *str = my_cstrcat("Hello", "guy", ' ');
    char *str1 = my_cstrcat("Helo", " h", '-');
    cr_assert(my_strcmp(str, "Hello guy") == 0);
    cr_assert(my_strcmp(str1, "Helo- h") == 0);
}

Test(is_alphanum, test_it15)
{
    cr_assert(is_alphanum('2') == 0);
    cr_assert(is_alphanum('_') == 0);
    cr_assert(is_alphanum('a') == 0);
    cr_assert(is_alphanum('A') == 0);
    cr_assert(is_alphanum('@') == 1);
}
