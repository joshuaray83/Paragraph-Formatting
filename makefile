word.exe: word.c word.o
	gcc -Wall -ansi -pedantic -c word.c
	gcc -o word.exe word.o
