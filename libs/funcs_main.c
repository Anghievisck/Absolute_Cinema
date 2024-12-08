#include"funcs_main.h"

//Sleep em segundos
void delay(float seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds) {
    }
}

//Adiciona um filme a um usuario
void adiciona_filme(User *usuario, List *geral, int *erro) {
    if(usuario == NULL) return;
    *erro = 0;
    int erro1, erro2;
    char option = 's';
    char *placeholder;
    
    while(option != 'n' && option != 'N'){
        placeholder = GetString("\nDigite o nome do filme: ");
    
        insert_elem(usuario->movies, placeholder, &erro1); 
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

//remove um filme de um usuario
void remove_filme(User *usuario, List *geral, int *erro) {
    *erro = 0;
    int erro1, erro2;
    char option = 's';
    char *placeholder;
    
    while(option != 'n' && option != 'N'){
        placeholder = GetString("\nDigite o nome do filme: ");
    
        remove_elem(usuario->movies, placeholder, &erro1); 
        remove_elem(geral, placeholder, &erro2);
        if(erro1 || erro2){
            printf("\nErro ao remover o filme...\n");
            *erro = 1;
            free(placeholder);
            return;
        }
    
        printf("\nDeseja remover outro filme? (S/N)\n>>> ");
        scanf("%c", &option);
    }
}

//faz a interface com o usuário para criar um usuário no sistema. Recebe a lista de filmes gerais
User* Cria_usuario(List *G, Tree *t) {
    int n_USP, erro;
    char* name;

    while(1){
        n_USP = GetInteger("Insira o seu numero USP: ", "O numero USP deve ser um numero...\n");
        if(FindUser(t, n_USP) != NULL){
            printf("Esse numero USP já foi cadastrado, favor verifique seu numero...\n");
        } else {
            break;
        }
    }

    name = GetString("Insira seu nome: ");

    List *L = Create_list(UNICA, &erro);
    if(erro){
        printf("\nErro ao criar lista de filmes\n");
        printf("Cadastro nao efetuado \n");
        free(name);
        return NULL;
    }

    

    User *u = CreateUser(n_USP, name, L, &erro);
    free(name);
    if(erro){
        printf("\nErro ao criar o usuario\n");
        printf("Cadastro nao efetuado \n");
        return NULL;
    }
    adiciona_filme(u, G, &erro);
    if(erro) {
        printf("Cadastro nao efetuado \n");
        return NULL;
    }

    return u;
}

//remove um usuário do sistema
void Remocao(Tree *t){
    if (IsTreeEmpty(t)) return;
    int n = GetInteger("Digite seu numero USP:\n>>> ", "O **NUMERO** USP deve ser um numero...\n");
<<<<<<< HEAD
    if(RemoveNode(&(t->root), n)) {
        printf("\nNo removido com sucesso!\n");
    }
    else
    printf("Usuario nao encontrado");
        
=======
    int diminuiu;
    aux_remove(&(t->root), n, &diminuiu, t);
    printf("\nNo removido com sucesso!\n");
>>>>>>> 1b427973e5bffe35f8b4d463d1c6b9ffd8eaf5e2
}

//Encontra os três filmes mais gostados
void EncontrarTresMaiores(List *l) {
    // Inicializa os 3 maiores com valores mínimos
    Node *maior1, *maior2, *maior3;
    maior1 = maior2 = maior3 = NULL;
    int m1, m2, m3;
    m1 = m2 = m3 = -1;
    Node *sup = l->inicio;

    while(sup != NULL) {
        if (sup->qnt_igual > m1) {
            // Atualiza os maiores
            maior3 = maior2;
            maior2 = maior1;
            maior1 = sup;
            m3 = m2;
            m2 = m1;
            m1 = sup->qnt_igual;
        } else if (sup->qnt_igual > m2) {
            maior3 = maior2;
            maior2 = sup;
            m3 = m2;
            m2 = sup->qnt_igual;
        } else if (sup->qnt_igual > m3) {
            maior3 = sup;
            m3 = sup->qnt_igual;
        }
        sup = sup->prox;
    }
    char *aux = (char*) malloc(sizeof(char)*LENGTH);
    printf("Os mais queridos filmes sao:\n");
    if(maior1 != NULL){
        strcpy(aux, maior1->info);
        to_lowercase(aux);
        to_uppercase_after_space(aux);
        printf("%s; ", aux);
    }else{
        printf("Nao ha filmes no registro");
        return;
    }
    if(maior2 !=NULL){
        strcpy(aux, maior2->info);
        to_lowercase(aux);
        to_uppercase_after_space(aux);
        printf("%s; ", aux);
    }else{
        return;
    }
    if(maior3 !=NULL){
        strcpy(aux, maior3->info);
        to_lowercase(aux);
        to_uppercase_after_space(aux);
        printf("%s", aux);
    }
    free(aux);
}

//Recomenda a um usuário pessoas para ver um filme novo
void RecomedacaoSimilar(Tree *t){
    if(IsTreeEmpty(t)) {
        printf("O sistema esta vazio");
        return;
    }
    User *temp, *eu;
    int max = 0;
    eu = FindUser(t, GetInteger("Digite o seu Numero USP: ", "O numero USP deve ser um numero"));
    SimilarUser(eu, t->root, &temp, &max);
    if(max == 0){
        printf("Voce é estranho, logo nao tem recomendacoes");
    }else{
        printf("Vai falar com o %s", temp->nome);
    }
}

//Recomenda alguém que tenha gostos muito diferentes
void RecomendacaoDiff(Tree *t){
    if(IsTreeEmpty(t)) {
        printf("O sistema esta vazio");
        return;
    }
    User *temp, *eu;
    int min = -1;
    eu = FindUser(t, GetInteger("Digite o seu Numero USP: ", "O numero USP deve ser um numero"));
    Diffuser(eu, t->root, &temp, &min);
    printf("Vai falar com o %s", temp->nome);
}

//Escreve em um arquivo todas as informacoes da arvore
void ExportTree(Tree *t){
    FILE *fh_output; // File handler, modo de saída

    fh_output = fopen("tree_data.txt", "w");

    if(fh_output == NULL) {
        printf("Nao foi possivel criar o arquivo");
        return;
    }
    else {
        printf("Arquivo criado");
    }

    int placeholder = 0;
    fprintf(fh_output, "a) Atualmente, a ABB possui um total de %d usuarios distintos\n", t->Number_of_nodes);
    fprintf(fh_output, "b) Atualmente, a altura da ABB é %d\n", Tree_height(t));
    fprintf(fh_output, "c) Atualmente, a maior diferenca de alturas da ABB é de %d\n", Maior_Gap(t));
    fprintf(fh_output, "\nDados dos usuarios: \n\n");
    TreeToArchive(t, "Numero USP", "Nome", "Filmes", fh_output);


    fclose(fh_output);
}