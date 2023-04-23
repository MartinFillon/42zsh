##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for compiling my lib
##

CC 	=	gcc
RM	=	rm -f

SRC	=	../../src/exec/utils.c		\
		../../src/builtins/env.c

TESTS	=	./test_exec_utils.c		\
			./test_builtin_env.c

CFLAGS		+=	-Werror -Wextra -Wall
CPPFLAGS	+=	-I../../include --coverage
LDFLAGS		+=	-L../../lib
LDLIBS		+=	-lmy -lcriterion

TEST_NAME	=	unit_tests

all: tests_run

unit_tests:
	@../../scripts/clean.sh
	$(CC) -o $(TEST_NAME) $(SRC) $(TESTS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

tests_run: unit_tests
	./$(TEST_NAME)

clean:
	@../../scripts/clean.sh

fclean:	clean
	@rm -f $(TEST_NAME)

.PHONY: tests_run unit_tests clean fclean
