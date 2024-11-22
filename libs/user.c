#include <stdio.h>
#include <string.h>

#include "user.h"

void DeleteUsers(User **u);
User* FindMax(User *u);

User* InsertUser(Tree *t, User *newUser){
    return SupInsertUser(t->root, newUser);
}

User* SupInsertUser(User *current, User *newUser){
    if(current == NULL){
        return newUser;
    }

    if(current->numero_usp > newUser->numero_usp){
        current->nextL = InsertUser(current->nextL, newUser);
    } else if(current->numero_usp < newUser->numero_usp) {
        current->nextR = InsertUser(current->nextR, newUser);
    } else {
        return current;
    }

    int balance;
    if(current->nextL == NULL && current->nextR == NULL){
        current->degree = 0;
        balance = 0;
    } else if(current->nextL == NULL || current->nextR == NULL){
        current->degree = (current->nextR == NULL) ? (current->nextL->degree + 1) : (current->nextR->degree + 1);
        balance = (current->nextR == NULL) ? (current->degree - 0) :  (0 - current->degree);
    } else {
        current->degree = (current->nextR > current->nextL) ? (current->nextR->degree + 1) : (current->nextL>degree + 1);
        balance = current->nextL->degree - current->nextR->degree;
    }

    if(balance > 1){
        if(newUser->numero_usp < current->nextL->numero_usp){
            return rotateRight(current);
        } else {
            current->nextL = rotateLeft(current->nextL);
            return rotateRight(current);
        }
    } else if(balance < -1){
        if(newUser->numero_usp < current->nextR->numero_usp){
            current->nextR = rotateRight(current->rotateRight);
            return rotateLeft(current);
        } else {
            return rotateLeft(current);
        }
    }

    return current;
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
