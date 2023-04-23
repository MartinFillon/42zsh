##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for my_lib
##

# Modules available:
# my_network my_file my_math my_map
# my_list my_stdio my_fmt
# my_stdlib my_vec my_str my_cstr

# Modules to use:
LIB	=	my_list my_btree my_map my_vec my_str my_cstr my_queue my_utils

NAME	=	libmy.a

all:
	@for i in $(LIB); do make -C $$i; done

clean:
	@for i in $(LIB); do make -C $$i clean >/dev/null; done
	@../scripts/clean.sh

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
