#include"lista_ordenada.h"

List* Create_list(int *erro) {
    *erro = 0;
    List *A = (List*) malloc(sizeof(List));
    if(A == NULL) {
        *erro = 1;
        return A;
    }
    A->inicio = NULL;
    A->fim = NULL;
    A->tamanho = 0;
    return A;
}


int isListEmpty(List *L) {
    if(L->inicio == NULL)
        return 1;
    return 0;
}

int ListSize(List *L) {
    return L->tamanho;
}


void insert_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    Node *new_node = (Node*) malloc(sizeof(Node));
    if(new_node == NULL) {
        *erro = 1;
        return;
    }
    new_node->info = (Elem)malloc(sizeof(char)*50);

    strcpy(new_node->info, X);

    if(isListEmpty(L)) {
        L->inicio = new_node;
        L->fim = new_node;
        new_node->prox = NULL;
        L->tamanho = L->tamanho + 1;
        return;
    }

    Node *aux = L->inicio;
    while(aux != NULL) {
        int v_comp = strcmp(new_node->info, aux->info);

        if(v_comp == 0) { //se a comparacao deu zero, significa que o elemento ja esta na lista
            free(new_node->info);
            free(new_node);
            *erro = 1;
            return;
        }
        else if(v_comp < 0) { //se for menor que zero, significa q esta no mprimeiro lugar, por causa de como as proximas comparacoes sao feitas
            new_node->prox = L->inicio;
            L->inicio = new_node;
            L->tamanho = L->tamanho + 1;
            return;
        }
        else {
            if(aux->prox == NULL) { //se o proximo do auxiliar eh NULL, significa que o aux eh o ultimo da lista
                L->fim = new_node;
                aux->prox = new_node;
                new_node->prox = NULL;
                L->tamanho = L->tamanho + 1;
                return;
            }
            else if(strcmp(new_node->info, aux->prox->info) < 0){ //adiciona um elemento entre aux e aux->prox
                new_node->prox = aux->prox;
                aux->prox = new_node;
                L->tamanho = L->tamanho + 1;
                return;
            }
            else { //se nao der para inserir ainda, passa para o proximo
                aux = aux->prox;
            }
        }
    }
}


int search_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    if(isListEmpty(L)) {
        *erro = 1;
        return 0;
    }
    
    Node *aux = L->inicio;
    while(aux != NULL) {
        int v_comp = strcmp(X, aux->info);
        if(v_comp == 0) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}


void remove_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    if(isListEmpty(L)) {
        *erro = 1;
        return;
    }
    Node *aux, *aux2;
    aux = L->inicio;

    if(strcmp(X, aux->info) != 0) {
        while(aux->prox != NULL) {
            int v_comp = strcmp(X, aux->prox->info);
            if(v_comp == 0) {
                aux2 = aux->prox;
                aux->prox = aux2->prox;
                if(aux2 == L->fim) {
                    L->fim = aux;
                }
                free(aux2->info);
                free(aux2);
                L->tamanho = L->tamanho - 1;
                return;
            }
            aux = aux->prox;
        }
        *erro = 1;
        return;
    }
    else {
        if(L->inicio == L->fim) {
            L->fim = NULL;
        }
        L->inicio = aux->prox;
        free(aux->info);
        free(aux);
        L->tamanho = L->tamanho - 1;
        return;
    }
    

}

void printList(List *L,int *erro) {
    *erro = 0;
    if(L == NULL || isListEmpty(L)) {
        *erro = 1;
        return;
    }
    Node *aux = L->inicio;
    while(aux != NULL) {
        printf("%s\n", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void remove_all_nodes(List *L) {
    Node *aux1, *aux2;
    aux1 = L->inicio;
    while (aux1 != NULL) {
        aux2 = aux1->prox;
        free(aux1->info);
        free(aux1);
        aux1 = aux2;
    }
    L->inicio = NULL;
    L->fim = NULL;
    L->tamanho = 0;
}

void DestroyList(List *L) {
    remove_all_nodes(L);
    free(L);
}