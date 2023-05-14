##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for my_list
##

CC = gcc

INCLUDE	=	-I../../include

SRC	=	./add.c			\
		./create.c		\
		./iterate.c		\
		./free.c		\
		./sort.c		\
		./remove.c		\
		./find.c

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
