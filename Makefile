##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for mysh
##

CC	=	gcc


SRC	=	./src/main.c								\
		./src/input/read.c							\
		./src/input/signal.c						\
		./src/input/args.c							\
		./src/input/variables.c						\
		./src/input/history.c						\
		./src/input/env.c							\
		./src/input/split_args.c					\
		./src/input/backticks.c 					\
		./src/input/subshell.c 						\
		./src/input/escaped_chars.c					\
		./src/input/globbings.c 					\
		./src/line_editing/termios.c 				\
		./src/line_editing/read_termios.c 			\
		./src/line_editing/manage_input.c 			\
		./src/line_editing/arrow.c					\
		./src/builtins/builtins.c					\
		./src/builtins/jobs.c						\
		./src/builtins/chdir.c						\
		./src/builtins/history.c					\
		./src/builtins/env.c						\
		./src/builtins/set.c						\
		./src/builtins/fg.c							\
		./src/builtins/alias.c						\
		./src/builtins/unalias.c					\
		./src/builtins/scripting/if.c 				\
		./src/builtins/scripting/foreach.c 			\
		./src/builtins/where.c 						\
		./src/builtins/which.c 						\
		./src/exec/exec.c							\
		./src/exec/process.c						\
		./src/exec/tree.c							\
		./src/exec/redirect.c						\
		./src/exec/pipe.c							\
		./src/exec/error.c							\
		./src/exec/utils.c							\
		./src/exec/jobs.c							\
		./src/middleware/middleware.c				\
		./src/middleware/semicolumn.c				\
		./src/middleware/exec_if_fail.c				\
		./src/middleware/exec_if_success.c			\
		./src/middleware/read_file.c				\
		./src/middleware/write_file.c				\
		./src/middleware/append_file.c				\
		./src/middleware/heredoc.c					\
		./src/middleware/utils.c					\
		./src/middleware/pipe.c						\
		./src/parser/symbol.c						\
		./src/parser/gen.c 							\


CFLAGS		+=	-Werror -Wextra -Wall
CPPFLAGS	+=	-I./include
LDFLAGS		+=	-L./lib
LDLIBS		+=	-lmy

ifeq ($(DEBUG),1)
	CFLAGS	+=	-g3 -fsanitize=address
	LDFLAGS	+=	-fsanitize=address
endif


OBJ		=	$(SRC:.c=.o)
NAME	=	42sh


all:	lib $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

tests_run: all
	make -C ./tests/unit_tests

func_run: all
	make -C ./tests/func_tests

lib:
	make -C ./lib

clean:
	$(RM) $(OBJ)
	@./scripts/clean.sh

fclean:	clean
	make -C ./lib fclean
	make -C ./tests/unit_tests fclean
	make -C ./tests/func_tests clean
	$(RM) $(NAME)

re:	fclean lib all

.PHONY: all lib clean fclean re
