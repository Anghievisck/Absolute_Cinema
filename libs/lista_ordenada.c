#include"lista_ordenada.h"

//Inicializa a lista
List* Create_list(int type, int *erro) {
    *erro = 0;
    List *A = (List*) malloc(sizeof(List));
    if(A == NULL) {
        *erro = 1;
        return A;
    }
    A->inicio = NULL;
    A->fim = NULL;
    A->tamanho = 0;
    A->tipo = type;
    return A;
}

//Verifica se a lista está vazia
int isListEmpty(List *L) {
    if(L->inicio == NULL)
        return 1;
    return 0;
}

//Retorna a quantidade de elementos da lista
int ListSize(List *L) {
    return L->tamanho;
}

//insere um novo elemento na lista de forma ordenada alfabeticamente
void insert_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    Node *new_node = (Node*) malloc(sizeof(Node));
    if(new_node == NULL) {
        *erro = 1;
        return;
    }
    new_node->info = (Elem)malloc(strlen(X) + 1); //aloca a memoria necessaria (o tamanho da string mais o NULL terminator)
    strcpy(new_node->info, X); //copia a string na variavel X para o novo bloco
    to_uppercase(new_node->info); //transforma tudo em uppercase
    
    new_node->qnt_igual = 1;

    if(isListEmpty(L)) { //se a lista estiver vazia, insere o elemento de forma especifica
        L->inicio = new_node;
        L->fim = new_node;
        new_node->prox = NULL;
        L->tamanho = L->tamanho + 1;
        return;
    }

    Node *aux = L->inicio;
    while(aux != NULL) { //se a lista nao estiver vazia, percorre a lista
        int v_comp = strcmp(new_node->info, aux->info);

        if(v_comp == 0) { //se a comparacao deu zero, significa que o elemento ja esta na lista
            free(new_node->info); //desaloca esse novo bloco
            free(new_node);
            if(L->tipo == UNICA)
                *erro = 1;
            else
                aux->qnt_igual = aux->qnt_igual + 1;
            return;
        }
        else if(v_comp < 0) { //se for menor que zero, significa q esta no inicio da lista, por causa de como as proximas comparacoes sao feitas
            new_node->prox = L->inicio;
            L->inicio = new_node;
            L->tamanho = L->tamanho + 1;
            return;
        }
        else { //se a comparacao for maior que zero
            if(aux->prox == NULL) { //se o proximo do auxiliar eh NULL, significa que o aux eh o ultimo da lista
                L->fim = new_node;
                aux->prox = new_node;
                new_node->prox = NULL;
                L->tamanho = L->tamanho + 1;
                return;
            }
            else if(strcmp(new_node->info, aux->prox->info) < 0){ //adiciona um elemento entre aux e aux->prox
                new_node->prox = aux->prox;
                aux->prox = new_node;
                L->tamanho = L->tamanho + 1;
                return;
            }
            else { //se nao der para inserir ainda, passa para o proximo
                aux = aux->prox;
            }
        }
    }
}

//procura se o elemento está na lista. se for uma lista com pesos, retorna o peso
int search_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    if(isListEmpty(L)) { //lista vazia
        *erro = 1;
        return 0;
    }
    
    Elem str = (Elem)malloc(strlen(X) + 1);
    strcpy(str, X);
    to_uppercase(str); //transforma o input X em uppercase

    Node *aux = L->inicio;
    while(aux != NULL) {
        int v_comp = strcmp(str, aux->info);
        if(v_comp == 0) { //se encontrou o valor
            free(str);
            if(L->tipo == UNICA)
                return 1;
            else
                return aux->qnt_igual;
        }
        else if(v_comp < 0) //se alfabeticamente ja passou do elemento que esta sendo procurado
            break;
        aux = aux->prox;
    }
    free(str);
    return 0;
}

//remove um elemento da lista ordenada. se for uma lista com pesos, subtrai um do peso do elemento
void remove_elem(List *L, Elem X, int *erro) {
    *erro = 0;
    if(isListEmpty(L)) { //lista vazia
        *erro = 1;
        return;
    }
    Node *aux, *aux2;
    aux = L->inicio;

    Elem str = (Elem)malloc(strlen(X) + 1);
    strcpy(str, X);
    to_uppercase(str); //transforma X em uppercase

    if(strcmp(str, aux->info) != 0) { //se o inicio nao é o elemento a ser removido
        while(aux->prox != NULL) { //percorre a lista toda
            int v_comp = strcmp(str, aux->prox->info);
            if(v_comp == 0) { //se achou o elemento a ser removido
                if(L->tipo == PESOS && aux->prox->qnt_igual > 1) //se for com peso e o peso for maior que 1
                    aux->prox->qnt_igual = aux->prox->qnt_igual - 1; //apenas subtrai o peso
                else { //caso contrario, remove o nó
                    aux2 = aux->prox;
                    aux->prox = aux2->prox;
                    if(aux2 == L->fim) //se o elemento era o fim da lista
                        L->fim = aux;
                    L->tamanho = L->tamanho - 1;
                    free(aux2->info);
                    free(aux2);
                }
                
                free(str);
                return;
            }
            else if (v_comp < 0) //se ja passou do elemento procurado, ou seja, o elemento a ser removido nao esta na lista
                break;
            aux = aux->prox;
        }
        *erro = 1;
        free(str);
        return;
    }
    else { //se o inicio é o elemento a ser removido
        if(L->tipo == PESOS && aux->qnt_igual > 1) //se for com peso e o peso for maior que 1
            aux->qnt_igual = aux->qnt_igual - 1; //apenas subtrai o peso
        else {
            if(L->inicio == L->fim) {
                L->fim = NULL;
            }
            L->inicio = aux->prox;
            free(aux->info);
            free(aux);
            L->tamanho = L->tamanho - 1;
        }
        free(str);
        return;
    }
}

//imprime a lista ordenada em ordem alfabética
void printList(List *L,int *erro) {
    *erro = 0;
    if(L == NULL || isListEmpty(L)) {
        *erro = 1;
        return;
    }
    
    Node *aux = L->inicio;
    while(aux != NULL) {
        Elem str = (Elem)malloc(strlen(aux->info)+1);
        strcpy(str, aux->info);
        to_lowercase(str);
        to_uppercase_after_space(str);
        if(L->tipo == UNICA)
            printf("%s\n", str);
        else 
            printf("%s: %d\n", str, aux->qnt_igual);
        aux = aux->prox;

        free(str);
    }
    printf("\n");
}

//tira todos os elementos da lista
void remove_all_nodes(List *L) {
    Node *aux1, *aux2;
    aux1 = L->inicio;
    while (aux1 != NULL) {
        aux2 = aux1->prox;
        free(aux1->info);
        free(aux1);
        aux1 = aux2;
    }
    L->inicio = NULL;
    L->fim = NULL;
    L->tamanho = 0;
}

//Desaloca a lista inteira
void DestroyList(List *L) {
    remove_all_nodes(L);
    free(L);
}

//retorna uma lista ordenada sem pesos com a interseção das duas listas nos parametros
List* CompareLists(List *L, List *G, int *erro) {
    Node *aux_L = L->inicio, *aux_G = G->inicio;
    List *C = Create_list(0, erro);
    while(aux_L != NULL && aux_G != NULL) { //enquanto uma das listas nao acabar
        int v_comp = strcmp(aux_L->info, aux_G->info);
        if(v_comp == 0) { //se os elementos sao iguais, adiciona-o a nova lista e passa para o proximo elemento nas duas listas
            insert_elem(C, aux_L->info, erro);
            aux_L = aux_L->prox;
            aux_G = aux_G->prox;
        }
        else if(v_comp > 0) //se o elemento da lista L for maior alfabeticamente que o da lista G, percorre 1 na lista G
            aux_G = aux_G->prox;
        else //similar ao else if anterior
            aux_L = aux_L->prox;
    }
    return C;
}

//retorna uma lista com pesos com a uniao das listas nos parametros
List* MergeLists(List *L, List *G, int *erro) {
    Node *aux;
    List *M = Create_list(1, erro);
    //percorre as duas listas adicionando os elementos na nova lista. duplicatas sao tratadas na funcao insert_elem
    aux = L->inicio;
    while(aux != NULL) {
        insert_elem(M, aux->info, erro);
        aux = aux->prox;
    }
    aux = G->inicio;
    while(aux != NULL) {
        insert_elem(M, aux->info, erro);
        aux = aux->prox;
    }
    return M;
}