#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "user.h"
#include "lista_ordenada.h"

User* FindMax(User*);
int SupInsertUser(User**, User*);
User* SupFindUser(User*, int);

User* CreateUser(int n_USP, char* name, List *L, int *erro) {
    *erro = 0;
    User *u = (User*)malloc(sizeof(User));
    if(u == NULL)
        *erro = 1;
    u->degree = 0;
    u->nextL = NULL;
    u->nextR = NULL;
    u->nome = (char*) malloc(strlen(name) + 1);
    strcpy(u->nome, name);
    u->numero_usp = n_USP;
    u->movies = L;

    return u;
}


void InsertUser(Tree **t, User *newUser, int *e){
    if(t == NULL || (*t) == NULL){
        *e = -1;
        return;
    }

    if((*t)->root == NULL){
        (*t)->root = newUser;
        *e = 0;
    } else {
        *e = SupInsertUser(&(*t)->root, newUser);
        if(*e == 0){
            BalanceTree(t, newUser->numero_usp);
        }
    }
}

int SupInsertUser(User **current, User *newUser){
    if(current == NULL){
        return -1;
    }

    if((*current) == NULL){
        (*current) = newUser;

        return 0;
    } else {
        if(newUser->numero_usp < (*current)->numero_usp){
            return SupInsertUser(&(*current)->nextL, newUser);
        } else if(newUser->numero_usp > (*current)->numero_usp){
            return SupInsertUser(&(*current)->nextR, newUser);
        } else {
            return 1;
        }
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

void DeleteUser(User **u){
    if(u == NULL || *u == NULL){
        return;
    }
    
    User *aux;

    if((*u)->nextL == NULL && (*u)->nextR == NULL){
        free((*u)->nome);
        //        DestroyList(u->favoriteMovies);

        free(*u);
        free(u);

        return;
    } else if((*u)->nextL == NULL || (*u)->nextR == NULL){
        aux = ((*u)->nextL == NULL) ? (*u)->nextR : (*u)->nextL;
    } else {
        aux = FindMax((*u));

        if(aux == NULL){
            aux = (*u)->nextR;
        }
    }

    if(aux == NULL){
        return;
    }

    free((*u)->nome);
    //    DestroyList((*u)->favoriteMovies);
    free((*u));

    *u = aux;
}

void DeleteUsers(User **u){
    if(u == NULL || *u == NULL){
        return;
    }

    DeleteUsers(&(*u)->nextL);
    DeleteUsers(&(*u)->nextR);

    free((*u)->nome);
    //    DestroyList(*u)->favoriteMovies);

    free((*u));
    *u = NULL;
}
