#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "user.h"
#include "lista_ordenada.h"

void SupPrintUsers(User*, char*, char*, char*);

void BalanceSubtree(User**, int n);
int UpdateDegree(User*);

Tree* CreateTree(int *e){
    *e = 0;
    Tree *newTree = (Tree *)malloc(sizeof(Tree));

    if(newTree == NULL){
        *e = 1;
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
        BalanceSubtree(&(*u)->nextR, n);
    } else {
        BalanceSubtree(&(*u)->nextL, n);
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

void PrintTree(Tree *t, char* p_number, char* p_string, char*p_list){
    SupPrintUsers(t->root, p_number, p_string, p_list);
}

void SupPrintUsers(User *u, char* p_number, char* p_string, char* p_list){
    int e;
    if(u == NULL){
        return;
    } else {
        SupPrintUsers(u->nextL, p_number, p_string, p_list);
        printf("%s: %d | %s: %s", p_number, u->numero_usp, p_string, u->nome);
        printf("\n%s: \n", p_list);
        printList(u->movies, &e);
        SupPrintUsers(u->nextR, p_number, p_string, p_list);
    }
}
