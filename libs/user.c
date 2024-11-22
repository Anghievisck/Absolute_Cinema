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
    u->favoriteMovies = Create_List();

    return u;
}

// Cria um novo usuário e insere ele na árvore
int InsertUser(Tree *t){
    User *u = CreateUser();

    if(FindUser(t, u->numero_usp) != NULL){
        return -1;
    }

    if(t == NULL){
        return 0;
    }

    if(t->root == NULL){
        t->root = u;
    } else if(t->root->numero_usp > u->numero_usp){
        return SupInsertUser(&t->root->nextL, u);
    } else {
        return SupInsertUser(&t->root->nextR, u);
    }
}

int SupInsertUser(User **current, User *u){
    if(*current == NULL){
        *current = u;
        return 1;
    } else {
    *current = ((*current)->numero_usp > u->numero_usp) ? (*current)->nextL : (*current)->nextR;
        return SupInsertUser(current, u);
    }
}

User* FindUser(Tree *t, int n){
    if(t->root->numero_usp == n){
        return t->root;
    } else {
        User *aux = (t->root->numero_usp > n) ? t->root->nextL : t->root->nextR;
        if(aux == NULL){
            return NULL;
        }

        return SupFindUser(aux, n);
    }
}

User* SupFindUser(User* u, int n){
    if(u->numero_usp == n){
        return u;
    } else {
        u = (u->numero_usp > n) ? u->nextL : u->nextR;
        if(u == NULL){
            return NULL;
        }

        return SupFindUser(u, n);
    }
}

User* FindMax(User *u){
    User* aux = u->nextL;
    while(aux != NULL){
        if(aux->nextR != NULL){
            User* sup = aux->nextR;
            if(sup->nextR == NULL){
                aux->nextR = sup->nextL;

                return sup;
            }
        } else {
            return aux;
        }

        aux = aux->nextR;
    }

    return aux;
}

void InsertMovie(User*){
    // em implementação
}

void DeleteUser(User **u){
    if(u == NULL || *u == NULL){
        return;
    }

    if((*u)->nextL == NULL && (*u)->nextR == NULL){
        free(u->name);
        DestroyList(u->favoriteMovies);

        free(u);

        return;
    } else if((*u)->nextL == NULL || (*u)->nextR == NULL){
        User *aux = ((*u)->nextL == NULL) ? (*u)->nextR : (*u)->nextL;
    } else {
        User *aux = FindMax((*u));

        if(aux == NULL){
            aux = (*u)->nextR;
        }
    }

    if(aux == NULL){
        return;
    }

    free((*u)->name);
    DestroyList((*u)->favoriteMovies);
    free((*u));

    *u = aux;
}

void DeleteUsers(User **u){
    if(u == NULL || *u == NULL){
        return;
    }

    DeleteUsers(&(*u)->nextL);
    DeleteUsers(&(*u)->nextR);

    free((*u)->name);
    DestroyList(*u)->favoriteMovies);

    free((*u));
    *u = NULL;
}
