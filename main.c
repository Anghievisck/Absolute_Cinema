#include <stdio.h>
#include <stdlib.h>

#include "libs/user.h"
#include "libs/bst.h"

User* CreateUser(){
    User *u = (User*)malloc(sizeof(User));

    if(u == NULL){
        return NULL;
    }

    printf("Insira o seu numero USP: ");
    scanf("%d", &u->numero_usp);

    u->nome = (char *)malloc(sizeof(char) * 150);

    printf("Insira seu nome: ");
    getchar();
    fgets(u->nome, 150, stdin);

    u->nextL = NULL;
    u->nextR = NULL;
    // u->movies = Create_List();
    u->degree = 1;

    return u;
}

void ExportTree(Tree *t){
    
}

int main(int argc, char* argv[]){
    Tree* t = CreateTree();

    if(t == NULL){
        printf("Deu erro");
        return -1;
    }

    User* newUser = CreateUser();
    printf("Test: %d\n", newUser->numero_usp);
    printf("Test: %s", newUser->nome);

    return 0;
}
