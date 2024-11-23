#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "user.h"

void SupPrintUsers(User*);

void BalanceSubtree(User**);
int UpdateDegree(User*);

Tree* Create(){
    Tree *newTree = (Tree *)malloc(sizeof(Tree));

    if(newTree == NULL){
        return NULL;
    } else {
        newTree->root = NULL;

        return newTree;
    }
}

/*
    Se a árvore existe, retorna 1 ou 0, respectivamente vazia ou
    não vazia, senão retorna -1.
*/
int IsTreeEmpty(Tree *t){
    if(t == NULL){
        return -1;
    } else if(t->root == NULL){
        return 1;
    } else {
        return 0;
    }
}

void Delete(Tree **t){
    if((*t)->root == NULL){
        free(t);
        t = NULL;

        return;
    } else {
        DeleteUsers(&(*t)->root);
    }
}

int GetBalance(User *u){
    if(u == NULL){
        return 0;
    } else {
        return UpdateDegree(u->nextL) - UpdateDegree(u->nextR);
    }
}

void BalanceTree(Tree **t, int n){
    if(t == NULL || *t == NULL){
        return;
    }

    BalanceSubtree(&(*t)->root, n);
}

void BalanceSubtree(User **u, int n){
    if(u == NULL || *u == NULL){
        return;
    }

    if(n > (*u)->numero_usp){
        BalanceSubtree(&(*u)->nextR);
    } else {
        BalanceSubtree(&(*u)->nextL);
    }

    (*u)->degree = UpdateDegree((*u));

    int balance = GetBalance((*u));
    if(balance > 1 && GetBalance((*u)->nextL) >= 0){
        *u = RotateRight(*u);
    }

    if(balance > 1 && GetBalance((*u)->nextL) < 0){
        (*u)->nextL = RotateLeft((*u)->nextL);
        *u = RotateRight(*u);
    }

    if(balance < -1 && GetBalance((*u)->nextR) >= 0){
        *u = RotateLeft(*u);
    }

    if(balance < -1 && GetBalance((*u)->nextR) < 0){
        (*u)->nextR = RotateRight((*u)->nextR);
        *u = RotateLeft(*u);
    }
}

User* RotateLeft(User* u){
    User* sup = u->nextR;
    User* aux = sup->nextL; 

    sup->nextL = u;
    u->nextR = aux;

    u->degree = UpdateDegree(u);
    sup->degree = UpdateDegree(sup);

    return sup;
}

User* RotateRight(User* u){
    User* sup = u->nextL;
    User* aux = sup->nextR; 

    sup->nextR = u;
    u->nextL = aux;

    u->degree = UpdateDegree(u);
    sup->degree = UpdateDegree(sup);

    return sup;
}

int UpdateDegree(User* current){
    if(current->nextL == NULL && current->nextR == NULL){
        current->degree = 0;
    } else if(current->nextL == NULL || current->nextR == NULL){
        current->degree = (current->nextR == NULL) ? (current->nextL->degree + 1) : (current->nextR->degree + 1);
    } else {
        current->degree = (current->nextR > current->nextL) ? (current->nextR->degree + 1) : (current->nextL->degree + 1);
    }

    return current->degree;
}

void PrintTree(Tree *t){
    SubPrintUsers(t->root);
}

void SupPrintUsers(User *u){
    if(u == NULL){
        return;
    } else {
        SupPrintUsers(u->nextL);
        printf("Numero USP: %d | Nome: %s", u->numero_usp, n->nome);
        printf("\nFilmes: \n");

        /*
        Node *aux = n->movies->inicio;
        for(int i = 0; i < ListSize(n->movies); i++){
            printf("    %s\n", aux->info);
            aux = aux->prox;
        }
        */
        SupPrintUsers(u->nextR);
    }
}
