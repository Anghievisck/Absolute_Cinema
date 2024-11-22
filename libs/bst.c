#include <string.h>

#include "bst.h"

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
