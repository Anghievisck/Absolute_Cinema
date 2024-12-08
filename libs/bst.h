#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>


typedef struct user User;

typedef struct tree{
    User *root;
    int Number_of_nodes;
}Tree;

Tree* CreateTree(int*);
int IsTreeEmpty(Tree*);
void Delete(Tree**);

void BalanceTree(Tree**, int n);
int insert_in_tree(User **p, User *x);
int Tree_height(Tree *A);
int Maior_Gap(Tree *t);
void MaxDiff(User *u, int *max);
int RemoveNode(User **raiz,int valor);

void PrintTree(Tree*, char*, char*, char*);
void TreeToArchive(Tree*, char*, char*, char*, FILE *);

#endif