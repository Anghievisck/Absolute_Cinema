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
    //*erro = 0;
    Node *new_node = (Node*) malloc(sizeof(Node));
    if(new_node == NULL) {
        *erro = 1;
        printf("jesus\n");
        return;
    }

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
            free(new_node);
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
/*void insert_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    Node *new_node = (Node*) malloc(sizeof(Node));
    if(new_node == NULL) {
        *erro = 1;
        new_node = (Node*) malloc(sizeof(Node));
        return;
    }
    strcpy(new_node->info, X);

    if(isListEmpty(L)) {
        L->inicio = new_node;
        L->fim = new_node;
        new_node->prox = NULL;
    }
    else {
        Node *aux = L->inicio;
        int v_comp;
        while(aux != NULL) {
            v_comp = strcmp(new_node->info, aux->info);

            if(v_comp == 0) {//se for igual a zero, significa que o filme ja está na lista
                *erro = 1;
                free(new_node);
                return;
            }
            else if(v_comp > 0) { //significa que alfabeticamente, a string do new_node é depois
                if(aux->prox == NULL) { //se o próximo for null, significa q é o ultimo elemento da lista
                    aux->prox = new_node;
                    L->fim = new_node;
                    new_node->prox = NULL;
                    break;
                }
                else if(strcmp(new_node->info, aux->prox->info) < 0) {//significa que o new_node é anterior ao próximo elemento de aux
                    new_node->prox = aux->prox;
                    aux->prox = new_node;
                    break;
                }
            }
            else { //se o new_node é o novo primeiro da lista
                new_node->prox = L->inicio;
                L->inicio = new_node;
                break;
            }

            aux = aux->prox;
        }
    }
    L->tamanho = L->tamanho + 1;
}*/


int search_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    if(isListEmpty(L)) {
        *erro = 1;
        return 0;
    }
    
    Node *aux = L->inicio;
    int v_comp = strcmp(X, aux->info);
    while(aux != NULL) {
        if(v_comp == 0) {
            return 1;
        }
        else if(v_comp > 0) {
            return 0;
        }
        aux = aux->prox;
    }
}


//void remove_elem(List *L, Elem X, int *erro) {

//}

void printList(List *L) {
    Node *aux = L->inicio;
    while(aux != NULL) {
        printf("%s\n", aux->info);
        aux = aux->prox;
    }
}