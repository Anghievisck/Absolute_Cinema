#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef char* Elem;

typedef struct no {
    Elem info;
    struct no *prox;
} Node;

typedef struct list {
    Node *inicio, *fim;
    int tamanho;
} List;

List* Create_list(int *erro);

int isListEmpty(List *L);
int ListSize(List *L);

void insert_elem(List *L, Elem X, int *erro);
int search_elem(List *L, Elem X, int *erro);
void remove_elem(List *L, Elem X, int *erro);


List* CompareLists(List *L, List *G);
List* MergeLists(List *L, List *G);

void printList(List *L, int *erro);

void remove_all_nodes(List *L);
void DestroyList(List *L);
