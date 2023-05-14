#!/bin/bash

find . \( \
	-name "*.gcda" -or \
	-name "*.gcno" -or \
	-name "vgcore*" -or \
	-name "*.core" -or \
	-name ".bash_history" \
	\) -delete
