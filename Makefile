all: ApacheLogs
ApacheLogs: lista.o main.o 
	gcc -Wall -o ApacheLogs lista.o main.o

lista.o: lista.c 
	gcc -Wall -o lista.o -c lista.c

main.o: main.c
	gcc -Wall -o main.o -c main.c	

