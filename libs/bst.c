#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "user.h"
#include "lista_ordenada.h"

void SupPrintUsers(User*, char*, char*, char*);

int aux_insert(User **p, User *x, int *cresceu);
//void BalanceSubtree(User**, int n);
//int UpdateDegree(User*);

Tree* CreateTree(int *e){
    *e = 0;
    Tree *newTree = (Tree *)malloc(sizeof(Tree));

    if(newTree == NULL){
        *e = 1;
        return NULL;
    } else {
        newTree->root = NULL;
        newTree->Number_of_nodes = 0;
        return newTree;
    }
}

void MaxDiff(User *u, int *max){
    if(u!=NULL){
        if((u->fb)*(u->fb) > (*max)*(*max)){
            *max = u->fb;
        }
        MaxDiff(u->nextL, max);
        MaxDiff(u->nextR, max);
    }

}
void DD(User **r) {
    User *pai = *r;
    User *filho = pai->nextR;
    pai->nextR = filho->nextL;
    filho->nextL = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

void EE(User **r) {
    User *pai = *r;
    User *filho = pai->nextL;
    pai->nextL = filho->nextR;
    filho->nextR = pai;
    pai->fb = 0;
    filho->fb = 0;
    *r = filho;
}

void ED(User **r) {
    User *pai = *r;
    User *filho = pai->nextL;
    User *neto = filho->nextR;
    pai->nextL=neto->nextR;
    filho->nextR = neto->nextL;
    neto->nextL = filho;
    neto->nextR = pai;
    switch(neto->fb) {
        case -1:
            pai->fb = 1;
            filho->fb = 0;
            break;
        case 0:
            pai->fb = 0;
            filho->fb = 0;
            break;
        case 1:
            pai->fb = 0;
            filho->fb = -1;
            break;
    }
    neto->fb = 0;
    *r = neto;
}

void DE(User **r) {
    User *pai = *r;
    User *filho = pai->nextR;
    User *neto = filho->nextL;
    pai->nextR=neto->nextL;
    filho->nextL = neto->nextR;
    neto->nextR = filho;
    neto->nextL = pai;
    switch(neto->fb) {
        case -1:
            pai->fb = 1;
            filho->fb = 0;
            break;
        case 0:
            pai->fb = 0;
            filho->fb = 0;
            break;
        case 1:
            pai->fb = 0;
            filho->fb = -1;
            break;
    }
    neto->fb = 0;
    *r = neto;
}


int insert_in_tree(User **p, User *x){
    int cresceu;
    return(aux_insert(p, x, &cresceu));
};
//Obs como NO e elem é meio que a mesma bomba no caso User vou ter que dar uma alterada no codigo do prof 
int aux_insert(User **p, User *x, int *cresceu){
    if(*p == NULL){
        *p = x;
        *cresceu = 1;
        return(1);
    }else if( x->numero_usp == (*p) -> numero_usp){
        return(0);
    }else if( x->numero_usp < (*p) -> numero_usp){
        if(aux_insert(&(*p)->nextL, x, cresceu)){
            if(*cresceu){
                switch((*p)->fb){
                    case -1:
                        if((*p)->nextL->fb == -1){
                           EE(p);
                        }else{
                           ED(p);
                        }
                        *cresceu = 0;
                        break;
                    case 0:
                        (*p)->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        (*p)->fb = 0;
                        *cresceu = 0;
                        break;
                }//fim do switch
            }//fim do if
            return(1);
        }//fim do if
        else return(0);
    }else if(x->numero_usp > (*p) -> numero_usp){
        if(aux_insert(&(*p)->nextR, x, cresceu)){
            if(*cresceu) {
                switch((*p)->fb){
                    case -1:
                        (*p)->fb = 0;
                        *cresceu = 0;
                        break;
                    case 0:
                        (*p)->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        if((*p)->nextR->fb == 1){
                           DD(p);
                        }else{
                           DE(p);
                        }
                        *cresceu = 0;
                        break;
                }//fim do switch
            }//fim do if
            return(1);
        }else return(0);
    }
};


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
    if((*t)->root == NULL){
        free(t);
        t = NULL;

        return;
    } else {
        DeleteUsers(&(*t)->root);
    }
    
}

int Node_height(User* p) {
    int alt_esq, alt_dir;
    if(p == NULL)
        return 0;
    alt_esq = 1 + Node_height(p->nextL);
    alt_dir = 1 + Node_height(p->nextR);
    if(alt_esq > alt_dir)
        return(alt_esq);
    return(alt_dir);
}
int Tree_height(Tree *A) {
    return(Node_height(A->root));
}

void PrintTree(Tree *t, char* p_number, char* p_string, char*p_list){
    SupPrintUsers(t->root, p_number, p_string, p_list);
}

void SupPrintUsers(User *u, char* p_number, char* p_string, char* p_list){
    int e;
    if(u == NULL){
        return;
    } else {
        SupPrintUsers(u->nextL, p_number, p_string, p_list);
        printf("%s: %d | %s: %s", p_number, u->numero_usp, p_string, u->nome);
        printf("\n%s: \n", p_list);
        printList(u->movies, &e);
        SupPrintUsers(u->nextR, p_number, p_string, p_list);
    }
}


/*int GetBalance(User *u){
    if(u == NULL){
        return 0;
    } else {
        return UpdateDegree(u->nextL) - UpdateDegree(u->nextR);
    }
}

void BalanceTree(Tree **t, int n){
    if(t == NULL || *t == NULL){
        return;
    }

    BalanceSubtree(&(*t)->root, n);
}

void BalanceSubtree(User **u, int n){
    if(u == NULL || *u == NULL){
        return;
    }

    if(n > (*u)->numero_usp){
        BalanceSubtree(&(*u)->nextR, n);
    } else {
        BalanceSubtree(&(*u)->nextL, n);
    }

    (*u)->degree = UpdateDegree((*u));

    int balance = GetBalance((*u));
    if(balance > 1 && GetBalance((*u)->nextL) >= 0){
        *u = RotateRight(*u);
    }

    if(balance > 1 && GetBalance((*u)->nextL) < 0){
        (*u)->nextL = RotateLeft((*u)->nextL);
        *u = RotateRight(*u);
    }

    if(balance < -1 && GetBalance((*u)->nextR) >= 0){
        *u = RotateLeft(*u);
    }

    if(balance < -1 && GetBalance((*u)->nextR) < 0){
        (*u)->nextR = RotateRight((*u)->nextR);
        *u = RotateLeft(*u);
    }
}

User* RotateLeft(User* u){
    User* sup = u->nextR;
    User* aux = sup->nextL; 

    sup->nextL = u;
    u->nextR = aux;

    u->degree = UpdateDegree(u);
    sup->degree = UpdateDegree(sup);

    return sup;
}

User* RotateRight(User* u){
    User* sup = u->nextL;
    User* aux = sup->nextR; 

    sup->nextR = u;
    u->nextL = aux;

    u->degree = UpdateDegree(u);
    sup->degree = UpdateDegree(sup);

    return sup;
}

int UpdateDegree(User* current){
    if(current->nextL == NULL && current->nextR == NULL){
        current->degree = 0;
    } else if(current->nextL == NULL || current->nextR == NULL){
        current->degree = (current->nextR == NULL) ? (current->nextL->degree + 1) : (current->nextR->degree + 1);
    } else {
        current->degree = (current->nextR > current->nextL) ? (current->nextR->degree + 1) : (current->nextL->degree + 1);
    }

    return current->degree;
}*/
