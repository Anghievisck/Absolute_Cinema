#include"libs/funcs_main.h"

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
        printf("11. Maior diferenca  entre alturas que existem entre as sub-arvores de algum no da arvore\n");
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
                insert_in_tree(t, Cria_usuario(mais_legais, t));
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
                RecomedacaoSimilar(t);
            break;

            case FILME_BEM_DIFERENTE:
                RecomendacaoDiff(t);
            break;
            
            case ARQUIVO_TEXTO:
                ExportTree(t);
            break;

            case NUMERO_NOS_ARVORE:
                printf("Ha %d nos na arvore. \n", t->Number_of_nodes);
            break;

            case ALTURA_ARVORE:
                printf("A altura da arvore e %d", Tree_height(t));
            break;

            case MAIOR_DIF_H_SUBARVORES:
                printf("A maior diferenca de altura e %d. \n", Maior_Gap(t));
            break;

            case RETIRAR_CADASTRO:
                Remocao(t);
            break;

            case ADICIONAR_FILME:
                adiciona_filme(FindUser(t, GetInteger("Digite o seu numero USP: ", "O numero USP deve ser um numero")), mais_legais, &erro);
            break;
            
            case REMOVER_FILME:
                remove_filme(FindUser(t, GetInteger("Digite o seu numero USP: ", "O numero USP deve ser um numero")), mais_legais, &erro);
            break;
            
            case FILMES_MAIS_QUERIDOS:
                EncontrarTresMaiores(mais_legais);
            break;

            case REINICIAR_SISTEMA:
                Delete(&t);
                DestroyList(mais_legais);
                int erro;
                t = CreateTree(&erro);
                mais_legais = Create_list(PESOS, &erro);
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


        delay(1);
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
