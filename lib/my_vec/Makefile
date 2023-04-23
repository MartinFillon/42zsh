##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for my_vec
##

CC = gcc

INCLUDE	=	-I../../include


SRC	=	./add.c			\
		./create.c		\
		./filter.c		\
		./find.c		\
		./reverse.c		\
		./free.c		\
		./iterate.c		\
		./remove.c		\
		./sort.c		\
		./utils.c

CFLAGS += -Werror -Wextra -Wall
CPPFLAGS += $(INCLUDE)

ifeq ($(DEBUG),1)
	CFLAGS += -g3
endif

OBJ	=	$(SRC:.c=.o)

NAME	=	../libmy.a

all:	$(OBJ)
	@ar cq $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

re:	clean all

.PHONY: all clean re
