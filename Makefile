##
## EPITECH PROJECT, 2025
## minnishell1
## File description:
## The makefile
##

NAME	=	mys

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
		src/dir_functions.c

INDESIRED	=	$(SRC:.c=.c~)

CRITERION	=	-lcriterion --coverage

all :	$(NAME)

$(NAME) :	$(SRC)
	@gcc -o $@ -g3 $(SRC)

clean :
	@rm -rf $(INDESIRED)

fclean :	clean
	@rm -rf $(NAME)

re :	fclean	all
