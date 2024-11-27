#ifndef BST_H
#define BST_H

typedef struct user User;

typedef struct tree{
    User *root;
}Tree;

Tree* CreateTree(int*);
int IsTreeEmpty(Tree*);
void Delete(Tree**);

void BalanceTree(Tree**, int n);
User* RotateLeft(User*);
User* RotateRight(User*);
int insert(User **p, User *x);
int aux_insert(User **p, User *x, int *cresceu);

void PrintTree(Tree*, char*, char*, char*);

#endif