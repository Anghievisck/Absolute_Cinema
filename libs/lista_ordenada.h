#include<stdlib.h>
#include<stdio.h>
#include"string_auxiliar.h"

enum tipo { //lista única guarda apenas uma cópia do elemento. tipo Peso guarda a quantidade de vezes que esse elemento foi adicionado
    UNICA = 0,
    PESOS = 1
};

typedef struct no {
    Elem info; //tipo herdado de string_auxiliar.h
    int qnt_igual;
    struct no *prox;
} Node;

typedef struct list {
    Node *inicio, *fim;
    int tamanho, tipo;
} List;

List* Create_list(int type, int *erro);

int isListEmpty(List *L);
int ListSize(List *L);

void insert_elem(List *L, Elem X, int *erro);
int search_elem(List *L, Elem X, int *erro);
void remove_elem(List *L, Elem X, int *erro);


List* CompareLists(List *L, List *G, int *erro);
List* MergeLists(List *L, List *G, int *erro);

void printList(List *L, int *erro);
void List_to_archive(List *L,FILE *arquivo, int *erro);

void remove_all_nodes(List *L);
void DestroyList(List *L);
