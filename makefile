main.o: main.c libs/lista_ordenada.h libs/user.h libs/bst.h
	gcc -c main.c

string_auxiliar.o: libs/string_auxiliar.c libs/string_auxiliar.h
	gcc -c libs/string_auxiliar.c

lista_ordenada.o: libs/lista_ordenada.c libs/lista_ordenada.h
	gcc -c libs/lista_ordenada.c

user.o: libs/user.c libs/user.h libs/lista_ordenada.h
	gcc -c libs/user.c

bst.o: libs/bst.c libs/bst.h libs/lista_ordenada.h
	gcc -c libs/bst.c

funcs_main.o: libs/funcs_main.c libs/bst.h libs/user.h libs/lista_ordenada.h
	gcc -c libs/funcs_main.c

all: main.o string_auxiliar.o lista_ordenada.o user.o bst.o funcs_main.o
	gcc -o main main.o lista_ordenada.o user.o bst.o string_auxiliar.o funcs_main.o

clean:
	rm *.o main

run:
	.\main.exe