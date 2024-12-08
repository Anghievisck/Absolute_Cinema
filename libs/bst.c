#include "user.h"
#include "lista_ordenada.h"

#include "bst.h"

void SupPrintUsers(User*, char*, char*, char*);
void SupToArchive(User *u, char* p_number, char* p_string, char* p_list, FILE *arquivo);

int aux_insert(User **p, User *x, int *cresceu, Tree *t);

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
        printf("%d\n", u->fb);
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

int insert_in_tree(Tree *t, User *x){
    int cresceu;
    return(aux_insert(&(t->root), x, &cresceu, t));
};
//Obs como NO e elem é meio que a mesma bomba no caso User vou ter que dar uma alterada no codigo do prof 
int aux_insert(User **p, User *x, int *cresceu, Tree *t){
    if(*p == NULL){
        *p = x;
        *cresceu = 1;
        t->Number_of_nodes = t->Number_of_nodes + 1;
        return(1);
    }else if( x->numero_usp == (*p) -> numero_usp){
        return(0);
    }else if( x->numero_usp < (*p) -> numero_usp){
        if(aux_insert(&(*p)->nextL, x, cresceu, t)){
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
        if(aux_insert(&(*p)->nextR, x, cresceu, t)){
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

//função suporte para Delete
void DeleteUsers(User **u){
    if(u == NULL || *u == NULL){
        return;
    }

    DeleteUsers(&(*u)->nextL);
    DeleteUsers(&(*u)->nextR);

    free((*u)->nome);
    DestroyList((*u)->movies);

    free((*u));
    *u = NULL;
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

int Maior_Gap(Tree *t){
    int maior=0;
    MaxDiff(t->root, &maior);
    //como pegamos os fatores de balanceamento pode ser o caso de ser menor que 0
    if(maior < 0){
        maior = maior - 2*maior; 
    }
    return(maior);
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

void TreeToArchive(Tree *t, char* p_number, char* p_string, char* p_list, FILE *arquivo) {
    SupToArchive(t->root, p_number, p_string, p_list, arquivo);
}

void SupToArchive(User *u, char* p_number, char* p_string, char* p_list, FILE *arquivo) {
    int e;
    if(u == NULL){
        return;
    } else {
        SupToArchive(u->nextL, p_number, p_string, p_list, arquivo);
        fprintf(arquivo, "%s: %d | %s: %s", p_number, u->numero_usp, p_string, u->nome);
        fprintf(arquivo, "\n%s: \n", p_list);
        List_to_archive(u->movies, arquivo, &e);
        SupToArchive(u->nextR, p_number, p_string, p_list, arquivo);
    }
}

int RemoveNode(User **raiz,int valor) {
    int controle;

    if(*raiz==NULL)
    {
        return 0;
    }
    if(valor < (*raiz)->numero_usp)
    {
        if((controle=RemoveNode(&((*raiz)->nextL),valor))==1)
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
        if ((controle=RemoveNode(&((*raiz)->nextR),valor))==1)
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
            free(nohAuxiliar->nome);
            DestroyList(nohAuxiliar->movies);
            free(nohAuxiliar);
            nohAuxiliar = NULL;
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
            RemoveNode(&(*raiz)->nextR,(*raiz)->numero_usp);
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