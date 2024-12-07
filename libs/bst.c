#include <string.h>
#include <stdlib.h>

#include "bst.h"
#include "user.h"
#include "lista_ordenada.h"

User* balanciar(User *);
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

int fbnode(User *r){
    return(Node_height(r->nextR)-Node_height(r->nextL));
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

User* balanciar(User *r){
    int fb = fbnode(r);
    if(fb < -1 && fbnode(r->nextR) <= 0){
        DD(&r);
    } else if(fb > 1 && fbnode(r->nextL) >= 0){
        EE(&r);
    } else if(fb > 1 && fbnode(r->nextL) < 0){
        DE(&r);
    } else if(fb < -1 && fbnode(r->nextR) >0){
        ED(&r);
    }

    return(r);
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

int remover2(User **raiz,int valor){
    int controle;

    if(*raiz==NULL)
    {
        printf("\nEste valor não existe\n");
        return 0;
    }
    if(valor < (*raiz)->numero_usp)
    {
        if((controle=remover2(&((*raiz)->nextL),valor))==1)
        {
            if(fbnode(*raiz)>=2)
            {
                if(Node_height((*raiz)->nextR->nextL)<=Node_height((*raiz)->nextR->nextR))
                    EE(raiz);
                else
                    ED(raiz);
            }
        }
    }
    if(valor>(*raiz)->numero_usp)
    {
        if ((controle=remover2(&((*raiz)->nextR),valor))==1)
        {

            if(fbnode(*raiz)>=2)
            {
                if(Node_height((*raiz)->nextL->nextR)<=Node_height((*raiz)->nextL->nextL))
                    DD(raiz);
                else
                    DE(raiz);
            }
        }
    }
    if((*raiz)->numero_usp==valor)
    {
        if(((*raiz)->nextL==NULL)||((*raiz)->nextR==NULL)) //Pai tem um filho ou nenhum filho
        {
            User *nohAuxiliar = *raiz;

            if((*raiz)->nextL!=NULL)
                *raiz=(*raiz)->nextL;
            else
                *raiz=(*raiz)->nextL;
            free(nohAuxiliar);
            nohAuxiliar = NULL;
            printf("\nNó removido com sucesso!\n");
        }
        else 
        {
        	//o pai tem dois filhos. 
        	//Substituir pelo nó mais a esquerda da subárvore da direita
            
            User *nohAuxiliar = (*raiz)->nextR;
            while(nohAuxiliar->nextL != NULL){
                nohAuxiliar = nohAuxiliar->nextL;
            }
            (*raiz)->numero_usp = nohAuxiliar->numero_usp;
            remover2(&(*raiz)->nextR,(*raiz)->numero_usp);
            if(fbnode(*raiz)>=2)
            {
                if(Node_height((*raiz)->nextL->nextR)<=Node_height((*raiz)->nextL->nextL))
                    DD(raiz);
                else
                    ED(raiz);
            }
        }
        return 1;
    }
    return controle;
}


User* Remove(User **r, int target){
    if(r == NULL){
        printf("Usuario nao encontrado. \n");
        return NULL;
    } else {
        if((*r)->numero_usp == target){
            if((*r)->nextL == NULL && (*r)->nextR == NULL){
                DeleteUser(r);
                return(NULL);
            } else {
                if((*r)->nextL != NULL && (*r)->nextR != NULL){
                    User **aux = &(*r)->nextL;
                    while((*aux)->nextR != NULL){
                        aux = &(*aux)->nextR;
                    }
                    User **temp = aux;
                    *aux = *r;
                    *r = *temp;
                    (*r)->nextL = Remove(&(*r)->nextL, target);
                    return(*r);
                }else{
                    User *aux;
                    if((*r)->nextL != NULL){
                        aux = (*r)->nextL;
                    }else{
                        aux = (*r)->nextR;
                    }
                    DeleteUser(r);
                    return(aux);
                }

            }

        } else{
            if(target < (*r)->numero_usp){
                (*r)->nextL = Remove(&(*r)->nextL, target);
            }else{
                (*r)->nextR = Remove(&(*r)->nextR, target);
            }
        }
        (*r) = balanciar(*r);
        return((*r));
    }
}
