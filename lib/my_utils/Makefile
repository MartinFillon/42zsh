##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for my_utils
##

CC = gcc

INCLUDE	=	-I../../include


SRC	=	./my_swap.c			\
		./my_vfree.c


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
