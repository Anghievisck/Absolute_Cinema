#include <string.h>
#include <stdlib.h>

#include "lista_ordenada.h"
#include "bst.h"

#include "user.h"

User* SupFindUser(User*, int);

//Cria o bloco de um usuário
User* CreateUser(int n_USP, char* name, List *L, int *erro) {
    *erro = 0;
    User *u = (User*)malloc(sizeof(User));
    if(u == NULL)
        *erro = 1;
    u->fb = 0;
    u->nextL = NULL;
    u->nextR = NULL;
    u->nome = (char*) malloc(strlen(name) + 1);
    strcpy(u->nome, name);
    u->numero_usp = n_USP;
    u->movies = L;

    return u;
}

//Busca pelo número se um usuário está na lista, retornando seu endereço
User* FindUser(Tree *t, int n){
    if(t->root == NULL){
        return NULL;
    } else if(t->root->numero_usp == n){
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


//retorna na entrada "atual" a pessoa com a maior quantidade de filmes identicos a um determinado usuário
void SimilarUser(User *eu, User *pretendente, User **atual, int *max) {
    if (pretendente != NULL) {
        if (eu->numero_usp != pretendente->numero_usp) {
            List *l;
            int erro = 0;

            // Compara listas de filmes
            l = CompareLists(eu->movies, pretendente->movies, &erro);
            
            // Verifica se a comparação foi bem-sucedida
            if (erro == 0 && l != NULL) {
                if (l->tamanho > *max) {
                    *atual = pretendente; // Atualiza o ponteiro para o usuário mais similar
                    *max = l->tamanho;   // Atualiza o valor máximo
                }
            }
        }

        // Recorre para os filhos da árvore
        SimilarUser(eu, pretendente->nextL, atual, max);
        SimilarUser(eu, pretendente->nextR, atual, max);
    }
}

//retorna na entrada "atual" a pessoa com a menor quantidade de filmes identicos a um determinado usuário
void Diffuser(User *eu, User *pretendente, User **atual, int *min){
    if(pretendente != NULL){
        if(eu->numero_usp != pretendente->numero_usp){
            List *l;
            int erro;
            l = CompareLists(eu->movies, pretendente->movies, &erro);
            if(l->tamanho > *min || *min == -1){
                *atual = pretendente;
                *min = l->tamanho;
            }
            DestroyList(l);
        }
        SimilarUser(eu, pretendente->nextL, atual, min);
        SimilarUser(eu, pretendente->nextR, atual, min);
    }
}
