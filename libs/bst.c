#include <string.h>

#include "user.h"

void SupBalanceTree(Tree**, User *u);

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
    if((*t)->root == NULL)){
        free(t)
        t = NULL;

        return;
    } else {
        DeleteUsers(&(*t)->root);
    }
}

int updateDegree(User* current){
    if(current->nextL == NULL && current->nextR == NULL){
        current->degree = 0;
    } else if(current->nextL == NULL || current->nextR == NULL){
        current->degree = (current->nextR == NULL) ? (current->nextL->degree + 1) : (current->nextR->degree + 1);
    } else {
        current->degree = (current->nextR > current->nextL) ? (current->nextR->degree + 1) : (current->nextL>degree + 1);
    }

    return current->degree;
}

User* rotateLeft(User* u){
    User* sup = u->nextR;
    User* aux = sup->nextL; 

    sup->nextL = u;
    u->nextR = aux;

    u->degree = getDegree(u);
    sup->degree = getDegree(sup);

    return sup;
}

User* rotateRight(User* u){
    User* sup = u->nextL;
    User* aux = sup->nextR; 

    sup->nextR = u;
    u->nextL = aux;

    u->degree = getDegree(u);
    sup->degree = getDegree(sup);

    return sup;
}
