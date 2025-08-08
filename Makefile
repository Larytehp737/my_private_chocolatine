##
## EPITECH PROJECT, 2025
## minnishell1
## File description:
## The makefile
##

NAME	=	mysh

SRC	=	src/main.c	\
		src/delim_functions.c	\
		src/mem_manip.c	\
		src/str_to_word_array.c	\
		src/utils.c	\
		src/utils1.c	\
		src/prompt.c	\
		src/command_man.c	\
		src/my_cd.c	\
		src/my_env.c	\
		src/my_exit.c	\
		src/my_setenv.c	\
		src/my_status_disp.c	\
		src/my_unsetenv.c	\
		src/array_2d_manips.c	\
		src/dir_functions.c	\
		src/cli_tools.c	\
		src/cli_parser.c	\
		src/cli_safety1.c	\
		src/for_pipe.c	\
		src/for_redir.c	\
		src/ut.c

TESTS_SRC	=	tests/test.c

vpath %.c src
vpath %.c tests

TO_BE_TESTED	=	src/delim_functions.c	\
					src/utils.c	\
					src/utils1.c	\
					src/cli_safety1.c	\
					src/ut.c

INDESIRED	=	$(SRC:.c=.c~)

CRITERION	=	-lcriterion --coverage

.PHONY :	all	$(NAME)	unit_tests	tests_run

all :	$(NAME)

$(NAME) :	$(SRC)
	@gcc -o $@ -g3 $(SRC)

unit_tests :	$(TESTS_SRC) $(TO_BE_TESTED)
	@gcc -o $@ $(TESTS_SRC) $(TO_BE_TESTED) $(CRITERION)

tests_run :	fclean unit_tests
	@./unit_tests

clean :
	@rm -rf $(INDESIRED)
	@rm -rf *.gc*

fclean :	clean
	@rm -rf $(NAME)
	@rm -rf unit_tests

re :	fclean	all
