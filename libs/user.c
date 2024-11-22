#include <stdio.h>
#include <string.h>

#include "user.h"

User* CreateUser();
void SupInsertUser(User **current, User *u);
void DeleteUsers(User **u);
User* FindMax(User *u);

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
    u->favoriteMovies = CreateList();

    return u;
}

// Cria um novo usuário e insere ele na árvore
void InsertUser(Tree *t){
    User *u = CreateUser();

    if(t == NULL){
        return;
    }

    if(t->root == NULL){
        t->root = u;
    } else if(t->root->numero_usp > u->numero_usp){
        SupInsertUser(&t->root->nextL, u);
    } else {
        SupInsertUser(&t->root->nextR, u);
    }
}

void SupInsertUser(User **current, User *u){
    if(*current == NULL){
        *current = u;
        return;
    } else if((*current)->numero_usp > u->numero_usp){
        SupInsertUser(&(*current)->nextL, u);
    } else {
        SupInsertUser(&(*current)->nextR, u);
    }
}

void DeleteUser(User **u){
    if(u == NULL || *u == NULL){
        return;
    }

    if((*u)->nextL == NULL && (*u)->nextR == NULL){
        free(u->name);
        DeleteList(u->favoriteMovies);

        free(u);

        return;
    } else if((*u)->nextL == NULL || (*u)->nextR == NULL){
        User *aux = ((*u)->nextL == NULL) ? (*u)->nextR : (*u)->nextL;

        free((*u)->name);
        DeleteList((*u)->favoriteMovies);
        free((*u));

        *u = aux;

        return;
    }

    User *aux = FindMax((*u));

    if(aux == NULL){
        return;
    }

    strcpy(u->name, aux->name);
    u->numero_usp = aux->numero_usp;
    u->favoriteMovies = aux->favoriteMovies;

    free(aux->name);
    DeleteList(aux)
}

User* FindMax(User *u){
    User* aux = u->nextL;
    while(aux->nextR != NULL){
        aux = aux->nextR;
    }

    return aux;
}

void DeleteUsers(User **u){
    if(u == NULL || *u == NULL){
        return;
    }

    DeleteUsers(&(*u)->nextL);
    DeleteUsers(&(*u)->nextR);

    free((*u)->name);
    DeleteList(*u)->favoriteMovies);

    free((*u));
    *u = NULL;
}
