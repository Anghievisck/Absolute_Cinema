#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "libs/user.h"
#include "libs/bst.h"
#include "libs/lista_ordenada.h"


void delay(float seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds) {
    }
}


void adiciona_filme(List *usuario, List *geral, int *erro) {
    *erro = 0;
    int erro1, erro2;
    char option = 's';
    char *placeholder;
    
    while(option != 'n' && option != 'N'){
        placeholder = GetString("\nDigite o nome do filme: ");
    
        insert_elem(usuario, placeholder, &erro1); 
        insert_elem(geral, placeholder, &erro2);
        if(erro1 || erro2){
            printf("\nErro ao adicionar o filme...\n");
            *erro = 1;
            free(placeholder);
            return;
        }
    
        printf("\nDeseja adicionar um novo filme? (S/N)\n>>> ");
        scanf("%c", &option);
    }
}

//faz a interface com o usuário para criar um usuário no sistema. Recebe a lista de filmes gerais
User* Cria_usuario(List *G) {
    int n_USP, erro;
    char* name;

    n_USP = GetInteger("Insira o seu numero USP: ", "O numero USP deve ser um numero...\n");

    name = GetString("Insira seu nome: ");

    List *L = Create_list(UNICA, &erro);
    if(erro){
        printf("\nErro ao criar lista de filmes\n");
        printf("Cadastro nao efetuado \n");
        free(name);
        return NULL;
    }

    adiciona_filme(L, G, &erro);
    if(erro) {
        printf("Cadastro nao efetuado \n");
        return NULL;
    }

    User *u = CreateUser(n_USP, name, L, &erro);
    free(name);
    if(erro){
        printf("\nErro ao criar o usuario\n");
        printf("Cadastro nao efetuado \n");
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
    ADICIONAR_FILME,
    REMOVER_FILME,
    FILMES_MAIS_QUERIDOS,
    REINICIAR_SISTEMA,
    FECHAR_PROGRAMA
} OPTIONS;


int main(int argc, char* argv[]){
    int erro, loop = 1, acao;

    Tree* t = CreateTree(&erro);
    if(erro){
        printf("Nao foi possivel criar o sistema");
        return -1;
    }

    List* mais_legais = Create_list(PESOS, &erro);
    if (erro) {
        printf("Nao foi possivel criar a lista de filmes");
    }

    while(loop) {
        printf("\n ==========================\n");
        printf("       Menu Principal     ");
        printf("\n ==========================\n");
        printf("1. Cadastrar usuario\n");
        printf("2. Listar alunos do sistema\n");
        printf("3. Buscar aluno no sistema\n");
        printf("4. Listar todos os filme preferidos pelos alunos\n");
        printf("5. Buscar filme\n");
        printf("6. Ver filme novo (buscar sugestoes de colegas)\n");
        printf("7. Sugestao de filme muito diferente\n");
        printf("8. Gerar arquivo de texto com todas as informacoes do sistema\n");
        printf("9. Quantidade de nos na arvore do sistema\n");
        printf("10. Altura da arvore do sistema\n");
        printf("11. Maior diferenca  entre alturas que existe entre as sub-arvores de algum no da arvore\n");
        printf("12. Retirar cadastro de um usuario\n");
        printf("13. Adicionar filme na lista de um usuario\n");
        printf("14. Remover filme da lista de um usuario\n");
        printf("15. Listar filmes mais queridos\n");
        printf("16. Reiniciar o sistema (apagar todas as informacoes)\n");
        printf("17. Fechar o programa\n");

        acao = GetInteger("\nO que deseja fazer? ", "Por favor, digite o NUMERO da acao...\n");
        acao--;

        printf("\n");
        switch(acao) {
            case NOVO_CADASTRO:
                insert_in_tree(&(t->root), Cria_usuario(mais_legais));
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

            case LISTAR_TODOS_FILMES:
                printf("Todos os filmes mais preferidos:\n");
                printList(mais_legais, &erro);
            break;

            case BUSCAR_FILME:
                if(search_elem(mais_legais, GetString("Digite o filme que deseja saber sobre: "), &erro)) {
                    printf("Alguem definitivamente gosta desse filme");
                }
                else
                    printf("Ninguem gosta desse filme");
            break;

            case VER_FILME_NOVO:

            break;

            case FECHAR_PROGRAMA:
                Delete(&t);
                DestroyList(mais_legais);
                printf("\nFechando o programa...\n");
                delay(1);
                return 0;
            break;

            default:
                printf("Digite uma acao valida...\n");
            break;
        } //fim do switch


        delay(3);
        printf("\nFazer proxima acao? [S/N (fechara o programa)]:\n");
        char option;
        scanf(" %c", &option);
        if(option == 'N' || option == 'n') {
            printf("\nFechando o programa...\n");
            delay(1);
            Delete(&t);
            DestroyList(mais_legais);
            return 0;
        }
    } //fim do while
    return 0;
}
