##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for mysh functionnal tests
##

all: run

setup:
	gcc -o my_divzero segfault.c

build:
	cp ../../mysh .

run: clean setup build
	./tester.sh

clean:
	rm -f *.core core
	rm -f mysh
	rm -f my_divzero

.PHONY: all clean run setup build
