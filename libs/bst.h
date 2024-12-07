#ifndef BST_H
#define BST_H

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
void MaxDiff(User *u, int *max);

void PrintTree(Tree*, char*, char*, char*);

#endif