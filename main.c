#include <stdio.h>
#include <stdlib.h>

#include "libs/user.h"

User* CreateUser(){
    User *u = (User*)malloc(sizeof(User));

    if(u == NULL){
        return NULL;
    }

    printf("Insira o seu numero USP: ");
    scanf("%d", &u->numero_usp);

    u->name = (char *)malloc(sizeof(char) * 150);

    printf("Insira seu nome: ");
    getchar();
    fgets(u->name, 150, stdin);

    u->nextL = NULL;
    u->nextR = NULL;
    u->favoriteMovies = Create_List();
    u->degree = 1;

    return u;
}

int main(int argc, char* argv[]){
    printf("test");

    return 0;
}
