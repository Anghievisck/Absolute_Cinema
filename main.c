#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libs/user.h"
#include "libs/bst.h"
#include "libs/lista_ordenada.h"

User* Cria_usuario() {
    int n_USP, erro, contador = 1;
    char* name = (char*)malloc(sizeof(char)*150);

    n_USP = GetInteger("Insira o seu numero USP: ", "O numero USP deve ser um numero...\n");

    printf("Insira seu nome: ");
    //getchar();
    fgets(name, 150, stdin);

    List *L = Create_list(UNICA, &erro);
    if(erro){
        printf("\nErro ao criar lista de filmes\n");
        free(name);
        return NULL;
    }

    char option = 's';
    char *placeholder = (char*)malloc(sizeof(char) * 150);
    *placeholder = 'a';
    if(placeholder == NULL){
        printf("\nErro ao criar o placeholder para o nome do filme\n");
        free(name);
        free(placeholder);
        return NULL;
    }
    
    while(option != 'n' && option != 'N'){
        printf("\nDigite o nome do filme: ");
        if(contador != 1)
            getchar();
        fgets(placeholder, 150, stdin);
    
        insert_elem(L, placeholder, &erro); 
        if(erro){
            printf("\nErro ao adicionar o filme...\n");
            free(name);
            free(placeholder);
            return NULL;
        }
    
        printf("\nDeseja adicionar um novo filme? (S/N)\n>>> ");
        scanf("%c", &option);
        contador++;
    }

    User *u = CreateUser(n_USP, name, L, &erro);
    free(name);
    free(placeholder);
    if(erro){
        printf("\nErro ao criar o usuario\n");
        return NULL;
    }
    return u;
}

void ExportTree(Tree *t){
    FILE *fh_output; // File handler, modo de saída

    fh_output = fopen("tree_data.txt", "w");

    int placeholder = 0;
    fprintf(fh_output, "a) Atualmente, a ABB possui um total de %d usuarios distintos\n", placeholder);
    fprintf(fh_output, "b) Atualmente, a altura da ABB é %d\n", t->root->degree);
    fprintf(fh_output, "c) Atualmente, a maior diferenca de alturas da ABB é de %d\n", placeholder);

    fclose(fh_output);
}


typedef enum {
    NOVO_CADASTRO,
    LISTAR_TODOS_ALUNOS,
    BUSCAR_USUARIO,
    LISTAR_TODOS_FILMES,
    BUSCAR_FILME,
    VER_FILME_NOVO,
    FILME_BEM_DIFERENTE,
    ARQUIVO_TEXTO,
    NUMERO_NOS_ARVORE,
    ALTURA_ARVORE,
    MAIOR_DIF_H_SUBARVORES,
    RETIRAR_CADASTRO,
    REMOVER_FILME,
    FILMES_MAIS_QUERIDOS,
    REINICIAR_SISTEMA,
    FECHAR_PROGRAMA
} OPTIONS;


int main(int argc, char* argv[]){
    int erro, loop = 1, acao;
    Tree* t = CreateTree(&erro);
    if(erro){
        printf("Não foi possivel criar o sistema");
        return -1;
    }

    while(loop) {
        printf("\n ==========================\n");
        printf("       Menu Principal     ");
        printf("\n ==========================\n");
        printf("1. Cadastrar usuario\n");
        printf("2. Listar alunos do sistema\n");
        printf("3. Buscar aluno no sistema\n");
        printf("4. Listar todos os filme preferidos pelos alunos\n");
        printf("5. Buscar filme e pessoas que gostam dele\n");
        printf("6. Ver filme novo (buscar sugestoes de colegas)\n");
        printf("7. Sugestao de filme muito diferente\n");
        printf("8. Gerar arquivo de texto com todas as informações do sistema\n");
        printf("9. Quantidade de nos na arvore do sistema\n");
        printf("10. Altura da arvore do sistema\n");
        printf("11. Maior diferenca  entre alturas que existe entre as sub-árvores de algum nó da árvore\n");
        printf("12. Retirar cadastro de um usuário\n");
        printf("13. Remover filme da lista de um usuário\n");
        printf("14. Listar filmes mais queridos\n");
        printf("15. Reiniciar o sistema (apagar todas as informacoes\n");
        printf("16. Fechar o programa\n");

        acao = GetInteger(" O que deseja fazer? ", "Por favor, digite o NUMERO da acao...\n");
        acao--;

        printf("\n");
        switch(acao) {
            case NOVO_CADASTRO:
                insert_in_tree(&(t->root), Cria_usuario());
                if(erro != 0) 
                    printf("\nErro ao colocar o usuario na arvore\n");
            break;

            case LISTAR_TODOS_ALUNOS:
                PrintTree(t, "Numero USP", "Nome", "Filmes");
            break;

            case BUSCAR_USUARIO:
                if (FindUser(t, GetInteger("Digite o Numero USP da pessoa que deseja procurar: ", "O numero USP deve ser um numero")) == NULL)
                    printf("O usuario nao esta no sistema");
                else
                printf("O usuario esta no sistema");
            break;

            //case LISTAR_TODOS_FILMES:

            //break;

            case FECHAR_PROGRAMA:
                Delete(&t);
                loop = 0;
            break;

            default:
                printf("Digite uma acao valida...\n");
            break;
        }
    }
    return 0;
}
