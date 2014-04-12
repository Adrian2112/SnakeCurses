files = linked_list.c
all:
		gcc -o snake main.c $(files) -lcurses
