#include <stdio.h>
#include <stdlib.h>

#include "libs/user.h"
#include "libs/bst.h"

User* CreateUser(){
    User *u = (User*)malloc(sizeof(User));

    if(u == NULL){
        return NULL;
    }

    printf("Insira o seu numero USP: ");
    scanf("%d", &u->numero_usp);

    u->nome = (char *)malloc(sizeof(char) * 150);

    printf("Insira seu nome: ");
    getchar();
    fgets(u->nome, 150, stdin);

    u->nextL = NULL;
    u->nextR = NULL;
    u->degree = 0;

    // u->movies = Create_List();
    // if(u->movies == NULL){
    //  printf("\nErro ao criar lista de filmes\n");
    //  return NULL;
    // }

    // char option = 's';
    // char *placeholder = (char*)malloc(sizeof(char) * 150);
    // if(placeholder == NULL){
    //  printf("\nErro ao criar o placeholder para o nome do filme\n");
    //  return NULL;
    // }
    //
    // int e;
    //
    // while(option != 'n' || option != 'N'){
    //  printf("\nDigite o nome do filme: ");
    //  getchar();
    //  fgets(placeholder, 150, stdin);
    //
    //  InsertElem(n->movies, placeholder, &e); 
    //  if(e != 0){
    //      printf("\nErro ao adicionar o filme...\n");
    //      return u;
    //  }
    //
    //  printf("\nDeseja adicionar um novo filme? (S\n)\n>>> ");
    //  scnaf("%c", &option);
    // }

    return u;
}

void ExportTree(Tree *t){
    
}

int main(int argc, char* argv[]){
    Tree* t = CreateTree();

    if(t == NULL){
        printf("Deu erro");
        return -1;
    }

    User* newUser = CreateUser();
    printf("Test: %d\n", newUser->numero_usp);
    printf("Test: %s", newUser->nome);

    return 0;
}
