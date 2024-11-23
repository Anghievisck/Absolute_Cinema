#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "user.h"
#include "lista_ordenada.h"

User* FindMax(User*);
int SupInsertUser(User**, User*);
User* SupFindUser(User*, int);

void InsertUser(Tree **t, User *newUser, int *e){
    if(t == NULL || (*t) == NULL){
        *e = -1;
        return;
    }

    if((*t)->root == NULL){
        (*t)->root = newUser;
        *e = 0;
        return;
    } else {
        *e = SupInsertUser(&(*t)->root, newUser);
        if(*e == 0){
            BalanceTree(t, newUser->numero_usp);
            return;
        } else {
            *e = status;
            return;
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
//Funçao a ser chamada na Main
User* Similar_User_Call(Tree *t, User *user){
    User *temp = NULL;
    int max = 0;
    Similar_User(t->root, user, &temp, &max);
    if(temp == NULL){
        //Nao me contive
        printf("VOCE E ESTRANHO, logo nao ha ninguem com os mesmos gostos");
        return(NULL);
    }else{
        return(temp);
    }
}
//verifica de forma recursiva qual o usuario + semelhante
void Similar_User(User *pretendente, User *user, User **atual ,int *max){
    if(pretendente == NULL){
        return;
    }
    if(pretendente != user){
        //Ve se o pretendente é melhor que o atual
        int number = Similar_User_Sup(user, pretendente);
        if(number > max){
            *atual=pretendente;
            *max=number;
        }
    }
    //Ve de maneira recursiva para o resto da arvore
    Similar_User(pretendente->nextL, user, atual, max);
    Similar_User(pretendente->nextR, user, atual, max);
}

// a literal unica diferenca entre essas de Diff para de as de Similaridade é um if 
User* Diff_User_Call(Tree *t, User *user){
    User *temp = NULL;
    int max = -1;
    Similar_User(t->root, user, &temp, &max);
    if(max == -1){
        printf("So tem tu na rede mane se liga");
    }
    return(temp);
}
void Diff_User(User *pretendente, User *user, User **atual ,int *max){
    if(pretendente == NULL){
        return;
    }
    if(pretendente != user){
        //Ve se o pretendente é melhor que o atual
        int number = Similar_User_Sup(user, pretendente);
        //Esse if aq que difere ja que em uma voce que maximizar e outra minimizar
        if(number < max || max == -1){
            *atual=pretendente;
            *max=number;
        }
    }
    //Ve de maneira recursiva para o resto da arvore
    Similar_User(pretendente->nextL, user, atual, max);
    Similar_User(pretendente->nextR, user, atual, max);
}
//Retorna a quantidade de filmes em comum entre dois usuarios
int Similar_User_Sup(User* user, User* atual){
    //Cria lista qua guarda a intesecção
    List *pretendentes;
    int erro;
    pretendentes = Create_list(0, &erro);
    if(pretendentes == NULL){
        return(0);
    }
    //Faz a intesecão
    pretendentes = CompareLists(user->movies, atual->movies, &erro);
    if(pretendentes == NULL){
        return(0);
    }
    int tamanho = pretendentes->tamanho;
    DestroyList(pretendentes);
    return(tamanho);
}
