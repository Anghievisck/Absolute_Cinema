#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "user.h"
#include "bst.h"
#include "lista_ordenada.h"

void delay(float seconds);

void adiciona_filme(User *usuario, List *geral, int *erro);
void remove_filme(User *usuario, List *geral, int *erro);

User* Cria_usuario(List *G, Tree *t);
void Remocao(Tree *t);

void EncontrarTresMaiores(List *l);
void RecomedacaoSimilar(Tree *t);
void RecomendacaoDiff(Tree *t);

void ExportTree(Tree *t);