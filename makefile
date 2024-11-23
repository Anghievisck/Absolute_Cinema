main.o: main.c libs/lista_ordenada.h
	gcc -c main.c

lista_ordenada.o: libs/lista_ordenada.c libs/lista_ordenada.h
	gcc -c libs/lista_ordenada.c

all: main.o lista_ordenada.o
	gcc -c libs/lista_ordenada.c
	gcc -c main.c
	gcc -o test main.o lista_ordenada.o

clean:
	rm *.o main

run:
	.\test.exe